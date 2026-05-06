#include "hash_index.h"

#include "hash_index_bucket.h"
#include "hash_index_dir.h"
#include "hash_index_iter.h"
#include "system/system.h"

#include <cmath>

HashIndex::HashIndex(
    const HeapFile& heap_file, size_t key_column_idx, FileId dir_file_id, FileId buckets_file_id, size_t N
)
    : heap_file(heap_file),
      key_column_idx(key_column_idx),
      dir_file_id(dir_file_id),
      buckets_file_id(buckets_file_id),
      dir(*this) {
  // In the dir the only value that is never 0 is the initial bucket count
  // If it's 0 it means the dir is new
  if (dir.get_initial_bucket_count() == 0) {
    this->N = N;
    dir.set_initial_bucket_count(N);
    dir.set_page_collector_pointer(-1);
    for (size_t i = 0; i < N; ++i) {
      size_t page_num = get_new_bucket_page();
      dir.set_bucket_page(i, page_num);
    }
  } else {
    this->N = dir.get_initial_bucket_count();
  }
  this->split_pointer = dir.get_split_pointer();
  this->depth = dir.get_depth();
}

uint32_t HashIndex::get_new_bucket_page() {
  auto reuse_page_num = dir.get_page_collector_pointer();
  if (reuse_page_num != -1) {
    BucketPage reuse_bucket(*this, reuse_page_num);
    dir.set_page_collector_pointer(reuse_bucket.get_overflow_pointer());
    reuse_bucket.set_overflow_pointer(-1);
    reuse_bucket.set_tuple_count(0);
    return reuse_page_num;
  }

  auto& new_page = buffer_mgr.append_page(buckets_file_id);
  auto res = new_page.get_page_number();
  new_page.unpin();
  return res;
}

uint32_t HashIndex::hash_to_bucket_page(uint64_t hash, size_t depth) const {
  auto bucket_idx = hash_to_bucket_idx(hash, depth);
  if (bucket_idx < split_pointer) {
    bucket_idx = hash_to_bucket_idx(hash, depth + 1);
  }
  return dir.get_bucket_page(bucket_idx);
}

uint32_t HashIndex::hash_to_bucket_idx(uint64_t hash, size_t depth) const {
  return hash % size_t(std::pow(2, depth) * N);
}

void HashIndex::insert_record(RID rid) {
  auto record = heap_file.get_record(rid);
  auto& key = record.values[key_column_idx];
  auto hash = key.get_hash();

  auto bucket_page_num = hash_to_bucket_page(hash, depth);
  auto current_bucket_page = std::make_unique<BucketPage>(*this, bucket_page_num);

  bool new_overflow_page = false;
  while (!current_bucket_page->try_insert_record(hash, rid)) {
    auto overflow_pointer = current_bucket_page->get_overflow_pointer();
    if (overflow_pointer == -1) {
      overflow_pointer = get_new_bucket_page();
      current_bucket_page->set_overflow_pointer(overflow_pointer);
      new_overflow_page = true;
    }
    current_bucket_page = std::make_unique<BucketPage>(*this, overflow_pointer);
  }

  if (new_overflow_page) {
    split();
  }
}

std::unique_ptr<RelationIter> HashIndex::get_iter(const Value& key) {
  return std::make_unique<HashIndexIter>(*this, key, key_column_idx);
}

void HashIndex::split() {
  size_t split_buckets_count = static_cast<int>(std::round(N * std::pow(2, depth)));
  size_t bucket_count = split_buckets_count + split_pointer;

  if (split_pointer == split_buckets_count) {
    ++depth;
    split_pointer = 0;
    dir.set_depth(depth);
  }

  int32_t split_bucket_page_number = dir.get_bucket_page(split_pointer);
  int32_t new_bucket_page_number = get_new_bucket_page();
  dir.set_bucket_page(bucket_count, new_bucket_page_number);

  redistribute(split_bucket_page_number, new_bucket_page_number);

  auto current_page_number = split_bucket_page_number;
  auto next_page_number = -1;
  auto unused_page_number = -1;

  while (current_page_number != -1) {
    BucketPage current_bucket_page(*this, current_page_number);
    next_page_number = current_bucket_page.get_overflow_pointer();

    if (next_page_number == -1)
      break;

    BucketPage next_bucket_page(*this, next_page_number);
    if (next_bucket_page.get_tuple_count() == 0) {
      current_bucket_page.set_overflow_pointer(-1);
      unused_page_number = next_page_number;
      break;
    }
    current_page_number = next_page_number;
    next_page_number = next_bucket_page.get_overflow_pointer();
  }

  // mark the chain of unused pages of old bucket as free
  while (unused_page_number != -1) {
    BucketPage unused_bucket_page(*this, unused_page_number);

    // save overflow_pointer before writing
    auto next_unused_page_number = unused_bucket_page.get_overflow_pointer();
    unused_bucket_page.set_overflow_pointer(dir.get_page_collector_pointer());
    dir.set_page_collector_pointer(unused_page_number);

    unused_page_number = next_unused_page_number;
  }

  ++split_pointer;
  dir.set_split_pointer(split_pointer);
}

void HashIndex::delete_record(RID rid) {
  auto record = heap_file.get_record(rid);
  assert(!record.invalid());
  auto& value = record.values[key_column_idx];
  auto hash = value.get_hash();

  int32_t current_page = hash_to_bucket_page(hash, depth);

  while (current_page != -1) {
    BucketPage bucket_page(*this, current_page);
    bucket_page.delete_record(rid);
    current_page = bucket_page.get_overflow_pointer();
  }
}

void HashIndex::redistribute(const int split_bucket_page_number, const int new_bucket_page_number) {
  auto read_bucket = std::make_unique<BucketPage>(*this, split_bucket_page_number);
  auto write_old_bucket = std::make_unique<BucketPage>(*this, split_bucket_page_number);
  auto write_new_bucket = std::make_unique<BucketPage>(*this, new_bucket_page_number);

  // must save tuple_count as it may change later when write_old_bucket receives inserts
  auto read_tuple_count = read_bucket->get_tuple_count();
  write_old_bucket->set_tuple_count(0);

  while (read_bucket != nullptr) {
    for (int i = 0; i < read_tuple_count; ++i) {
      HashIndexRecord hash_record = read_bucket->get_record(i);
      int32_t record_bucket_idx = hash_to_bucket_idx(hash_record.hash, depth + 1);
      int32_t old_bucket_idx = hash_to_bucket_idx(hash_record.hash, depth);

      if (record_bucket_idx == old_bucket_idx) {
        if (!write_old_bucket->try_insert_record(hash_record.hash, hash_record.rid)) {
          auto old_overflow = write_old_bucket->get_overflow_pointer();
          // reader is not finished yet, and old writer must be behind or at same position
          // than reader, so overflow must exist
          assert(old_overflow != -1);
          write_old_bucket = std::make_unique<BucketPage>(*this, old_overflow);
          write_old_bucket->try_insert_record(hash_record.hash, hash_record.rid);
        }
      } else {
        if (!write_new_bucket->try_insert_record(hash_record.hash, hash_record.rid)) {
          auto new_page_number = get_new_bucket_page();
          write_new_bucket->set_overflow_pointer(new_page_number);
          write_new_bucket = std::make_unique<BucketPage>(*this, new_page_number);
          write_new_bucket->try_insert_record(hash_record.hash, hash_record.rid);
        }
      }
    }
    // keep reading for next iteration if overflow exists
    if (auto overflow_pointer = read_bucket->get_overflow_pointer(); overflow_pointer != -1) {
      read_bucket = std::make_unique<BucketPage>(*this, overflow_pointer);
      read_tuple_count = read_bucket->get_tuple_count();
      read_bucket->set_tuple_count(0);
    } else {
      read_bucket = nullptr;
    }
  }
}