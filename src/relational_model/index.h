#pragma once

#include <memory>

#include "relational_model/relation_iter.h"
#include "relational_model/value.h"
#include "relational_model/record.h"

using IndexId = size_t;

enum class IndexType { NONE, B_PLUS_TREE, LINEAR_HASH_INDEX };

class Index {
  friend class Catalog;
  friend class HashIndex;

public:
  virtual ~Index() = default;

  virtual std::unique_ptr<RelationIter> get_iter(const Value& key) = 0;

  virtual IndexType get_type() = 0;

  virtual size_t get_key_column_idx() = 0;

private:
  virtual void insert_record(RID rid) = 0;

  virtual void delete_record(RID rid) = 0;
};