#pragma once

#include "hash_index.h"
#include "relational_model/relation_iter.h"
#include "storage/linear_hash_index/hash_index_bucket.h"

class HashIndexIter : public RelationIter {
public:
  HashIndexIter(HashIndex& h_idx, const Value& key, size_t key_column_idx);

  virtual void begin() override;

  virtual Record next() override;

  virtual void reset() override;

private:
  HashIndex& h_idx;

  const Value key;

  const size_t key_column_idx;

  std::unique_ptr<BucketPage> current_bucket;

  int64_t current_bucket_pos;
};
