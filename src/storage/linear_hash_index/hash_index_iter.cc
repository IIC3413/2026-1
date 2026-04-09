#include "hash_index_iter.h"

HashIndexIter::HashIndexIter(HashIndex& h_idx, const Value& key, size_t key_column_idx)
    : h_idx(h_idx),
      key(key),
      key_column_idx(key_column_idx) {}

void HashIndexIter::begin() {
  reset();
}

void HashIndexIter::reset() {
  auto depth = h_idx.dir.get_depth();
  auto bucket_page = h_idx.hash_to_bucket_page(key.get_hash(), depth);
  current_bucket = std::make_unique<BucketPage>(h_idx, bucket_page);
  current_bucket_pos = 0;
}

Record HashIndexIter::next() {
  while (true) {
    if (current_bucket_pos < current_bucket->get_tuple_count()) {
      auto bucket_record = current_bucket->get_record(current_bucket_pos);
      auto current_record = h_idx.heap_file.get_record(bucket_record.rid);

      auto& value = current_record.values[key_column_idx];
      ++current_bucket_pos;

      // important to check this as we might lose information when hashing string values
      if (value == key) {
        return current_record;
      }

    } else if (current_bucket->get_overflow_pointer() != -1) {
      current_bucket = std::make_unique<BucketPage>(h_idx, current_bucket->get_overflow_pointer());
      current_bucket_pos = 0;
    } else {
      return Record();
    }
  }
}
