#pragma once

#include "hash_table.h"
#include "relational_model/relation_iter.h"

class HashTableIter : public RelationIter {
public:
  HashTableIter(const HashTable& htbl, const Value& key);

  void begin() override;

  Record next() override;

  void reset() override;

private:
  const HashTable& htbl;

  const Value key;

  int column_idx;

  HashTable::TableEntry current_hash_table_entry;

  uint64_t current_record_buffer_pos = -1;
};