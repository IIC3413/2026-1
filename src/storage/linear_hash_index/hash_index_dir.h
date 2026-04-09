#pragma once

#include "storage/page.h"

class HashIndex;

class HashIndexDir {
  friend class HashIndex;
public:
  static constexpr size_t INITIAL_BUCKET_COUNT_OFFSET = 0;
  static constexpr size_t SPLIT_POINTER_OFFSET = 4;
  static constexpr size_t DEPTH_OFFSET = 8;
  static constexpr size_t PAGE_COLLECTOR_OFFSET = 12;

  static constexpr size_t HEADER_SIZE = 16;

  HashIndexDir(const HashIndex& h_idx);

  ~HashIndexDir();

  size_t get_bucket_page(size_t idx) const;
  void set_bucket_page(size_t idx, uint32_t page);

  size_t get_split_pointer();
  size_t get_initial_bucket_count();
  size_t get_depth();

  // if page_collector_pointer == -1, no page is available
  int32_t get_page_collector_pointer();
  void set_page_collector_pointer(int32_t page_collector_pointer);

  void set_split_pointer(size_t new_split_pointer);
  void set_initial_bucket_count(size_t initial_bucket_count);
  void set_depth(size_t new_depth);

private:
  const HashIndex& h_idx;

  Page& first_page;
};

