#include "hash_table_iter.h"

HashTableIter::HashTableIter(const HashTable& htbl, const Value& key)
    : htbl(htbl),
      key(key) {
  this->column_idx = htbl.column_idx;
}

void HashTableIter::begin() {
  auto hash = key.get_hash();
  uint64_t encoded_value = key.encoded();

  auto probe_slot = hash % HashTable::CAPACITY;

  current_hash_table_entry.head_offset = uint64_t(-1);

  // TODO: Problema 2

  current_record_buffer_pos = current_hash_table_entry.head_offset;
}

Record HashTableIter::next() {
  // TODO: Problema 2
  return Record();
}

void HashTableIter::reset() {
  // HINT: Si begin encuentra la primera ocurrencia correctamente no necesitan hacer nada aquí
  current_record_buffer_pos = current_hash_table_entry.head_offset;
}