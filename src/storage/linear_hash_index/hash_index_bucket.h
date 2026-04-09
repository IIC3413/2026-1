#pragma once

#include "hash_index.h"
#include "relational_model/record.h"
#include "storage/rid.h"

// [tuple_count | overflow_pointer] 8 + 8 = 16 bytes
// [key | page_number | dir_slot] 8 + 4 + 4 = 16 bytes

class BucketPage {
public:
  static constexpr size_t TUPLE_COUNT_OFFSET = 0;
  static constexpr size_t OVERFLOW_POINTER_OFFSET = 8;

  static constexpr size_t HEADER_SIZE = 16;

  static constexpr size_t MAX_VALUES_PER_BUCKET = (Page::SIZE - HEADER_SIZE) / sizeof(HashIndexRecord);

  HashIndex& hash_index;

  Page& page;

  BucketPage(HashIndex& hash_index, int32_t page_number);

  ~BucketPage();

  // returns true if it was inserted
  bool try_insert_record(uint64_t hash, RID rid);

  void set_record(size_t pos, HashIndexRecord record);
  void delete_record(RID rid);

  HashIndexRecord get_record(size_t pos);

  int64_t get_tuple_count() const;

  // returns -1 if no overflow page exists
  int64_t get_overflow_pointer() const;

  void set_tuple_count(int64_t new_tuple_count);

  // -1 means no overflow
  void set_overflow_pointer(int64_t new_overflow_pointer);
};
