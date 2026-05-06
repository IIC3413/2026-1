#include "hash_table.h"

#include "hash_table_iter.h"

HashTable::HashTable(const int column_idx, std::vector<DataType> datatypes)
    : column_idx(column_idx),
      datatypes(datatypes) {
  probe_table = new TableEntry[CAPACITY];
  record_buffer = new char[RECORD_BUFFER_SIZE];
  for (auto i = 0; i < CAPACITY; ++i) {
    probe_table[i].head_offset = uint64_t(-1); // -1 means empty
  }
}

HashTable::~HashTable() {
  delete[] probe_table;
  delete[] record_buffer;
}

bool HashTable::try_insert_record(const Record& record) {
  auto needed_buffer_size = record.get_size_for_serialize() + sizeof(uint64_t);
  if (record_buffer_offset + needed_buffer_size > RECORD_BUFFER_SIZE) {
    return false;
  }

  auto hash = record.values[column_idx].get_hash();
  uint64_t encoded_value = record.values[column_idx].encoded();

  auto probe_slot = hash % CAPACITY;

  // TODO: Problema 1

  return false;
}

void HashTable::reset() {
  for (auto i = 0; i < CAPACITY; ++i) {
    probe_table[i].head_offset = uint64_t(-1); // -1 means empty
  }
  record_buffer_offset = 0;
  entries = 0;
}

std::unique_ptr<HashTableIter> HashTable::probe(const Value& key) {
  return std::make_unique<HashTableIter>(*this, key);
}

void HashTable::print_hash_table(std::ostream& os) {
  size_t entry_count = 0;

  for (size_t i = 0; i < CAPACITY && entry_count < entries; ++i) {
    auto entry = probe_table[i];

    if (entry.head_offset != uint64_t(-1)) {
      ++entry_count;

      Record record = Record::deserialize(record_buffer + entry.head_offset + sizeof(int64_t), datatypes);

      // position in probe_table|key
      os << i << "|";
      if (datatypes[column_idx] == DataType::INT) {
        os << entry.encoded_value << "\n";
      } else {
        os << record.values[column_idx].as_string() << "\n";
      }

      // Record chain
      size_t record_count = 0;
      size_t current_record_pos = entry.head_offset;

      while (current_record_pos != uint64_t(-1)) {
        Record record = Record::deserialize(record_buffer + current_record_pos + sizeof(int64_t), datatypes);

        os << record_count << ":(" << record.to_string() << ")\n";

        int64_t next_record;
        memcpy(&next_record, record_buffer + current_record_pos, sizeof(int64_t));

        current_record_pos = next_record;
        ++record_count;
      }
      os << "\n";
    }
  }
}