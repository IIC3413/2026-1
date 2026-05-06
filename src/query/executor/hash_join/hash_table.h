#pragma once

#include "relational_model/record.h"

#include <cstdint>
#include <memory>

class HashTableIter;

class HashTable {
public:
  static constexpr auto CAPACITY = 4096;
  static constexpr auto MAX_ENTRIES = 3000;

  static constexpr auto RECORD_BUFFER_SIZE = 1024 * 1024; // 1 MB

  struct TableEntry {
    uint64_t hash;
    uint64_t encoded_value;
    uint64_t head_offset;
  };

  HashTable(int column_idx, std::vector<DataType> datatypes);

  ~HashTable();

  bool try_insert_record(const Record& record);
  void reset();

  std::unique_ptr<HashTableIter> probe(const Value& key);

  void print_hash_table(std::ostream& os);

  int column_idx;
  std::vector<DataType> datatypes;

  uint64_t entries = 0;
  uint64_t record_buffer_offset = 0;

  TableEntry* probe_table;
  char* record_buffer;
};