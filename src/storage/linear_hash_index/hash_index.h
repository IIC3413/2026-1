#pragma once

#include "hash_index_dir.h"
#include "relational_model/index.h"
#include "relational_model/record.h"
#include "relational_model/relation_iter.h"
#include "storage/file_id.h"
#include "storage/heap_file/heap_file.h"
#include "storage/rid.h"

#include <memory>

struct HashIndexRecord {
  uint64_t hash;
  RID rid;

  HashIndexRecord(uint64_t hash, RID rid)
      : hash(hash),
        rid(rid) {}
};

class HashIndex : public Index {
public:
  static constexpr size_t DEFAULT_INITIAL_BUCKETS = 3;

  HashIndex(
      const HeapFile& heap_file,
      size_t key_col_idx,
      FileId dir_file_id,
      FileId buckets_file_id,
      size_t N = DEFAULT_INITIAL_BUCKETS
  );

  IndexType get_type() override {
    return IndexType::LINEAR_HASH_INDEX;
  }

  size_t get_key_column_idx() override {
    return key_column_idx;
  }

  uint32_t hash_to_bucket_page(uint64_t hash, size_t depth) const;
  uint32_t hash_to_bucket_idx(uint64_t hash, size_t depth) const;

  // gets a new page number for a bucket, reusing an old unused page if available
  uint32_t get_new_bucket_page();

  void insert_record(RID rid) override;
  void delete_record(RID rid) override;

  void split();
  void redistribute(const int split_bucket_page_number, const int new_bucket_page_number);

  std::unique_ptr<RelationIter> get_iter(const Value& key) override;

  const HeapFile& heap_file;

  const size_t key_column_idx;

  const FileId dir_file_id;
  const FileId buckets_file_id;

  HashIndexDir dir;

  // initial number of buckets
  size_t N;

  // index of the current hash function
  size_t depth;

  size_t split_pointer;
};