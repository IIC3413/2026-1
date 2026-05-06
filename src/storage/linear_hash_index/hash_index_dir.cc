#include "hash_index_dir.h"

#include "hash_index.h"
#include "system/system.h"

HashIndexDir::HashIndexDir(const HashIndex& h_idx)
    : h_idx(h_idx),
      first_page(buffer_mgr.get_page(h_idx.dir_file_id, 0)) {}

HashIndexDir::~HashIndexDir() {
  first_page.unpin();
}

size_t HashIndexDir::get_depth() {
  return first_page.read_int32(DEPTH_OFFSET);
}

size_t HashIndexDir::get_split_pointer() {
  return first_page.read_int32(SPLIT_POINTER_OFFSET);
}

size_t HashIndexDir::get_initial_bucket_count() {
  return first_page.read_int32(INITIAL_BUCKET_COUNT_OFFSET);
}

int32_t HashIndexDir::get_page_collector_pointer() {
  return first_page.read_int32(PAGE_COLLECTOR_OFFSET);
}

void HashIndexDir::set_depth(size_t new_depth) {
  first_page.write_int32(DEPTH_OFFSET, new_depth);
}

void HashIndexDir::set_split_pointer(size_t new_split_pointer) {
  first_page.write_int32(SPLIT_POINTER_OFFSET, new_split_pointer);
}

void HashIndexDir::set_initial_bucket_count(size_t initial_bucket_count) {
  first_page.write_int32(INITIAL_BUCKET_COUNT_OFFSET, initial_bucket_count);
}

void HashIndexDir::set_page_collector_pointer(int32_t page_number) {
  first_page.write_int32(PAGE_COLLECTOR_OFFSET, page_number);
}

size_t HashIndexDir::get_bucket_page(size_t idx) const {
  size_t absolute_offset = HEADER_SIZE + idx * sizeof(int32_t);

  auto page_num = absolute_offset / Page::SIZE;
  auto pos = absolute_offset % Page::SIZE;

  if (page_num == 0) {
    return first_page.read_int32(pos);
  } else {
    auto& other_page = buffer_mgr.get_page(h_idx.dir_file_id, page_num);
    auto res = other_page.read_int32(pos);
    other_page.unpin();
    return res;
  }
}

void HashIndexDir::set_bucket_page(size_t idx, uint32_t bucket_page) {
  size_t absolute_offset = HEADER_SIZE + idx * sizeof(int32_t);

  auto page_num = absolute_offset / Page::SIZE;
  auto pos = absolute_offset % Page::SIZE;

  if (page_num == 0) {
    first_page.write_int32(pos, bucket_page);
  } else {
    auto& other_page = buffer_mgr.get_page(h_idx.dir_file_id, page_num);
    other_page.write_int32(pos, bucket_page);
    other_page.unpin();
  }
}
