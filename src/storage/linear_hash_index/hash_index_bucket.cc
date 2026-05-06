#include "hash_index_bucket.h"

#include "system/system.h"

BucketPage::BucketPage(HashIndex& hash_index, int32_t page_number)
    : hash_index(hash_index),
      page(buffer_mgr.get_page(hash_index.buckets_file_id, page_number)) {
  if (get_overflow_pointer() == 0) {
    set_overflow_pointer(-1);
  }
}

BucketPage::~BucketPage() {
  page.unpin();
}

int64_t BucketPage::get_tuple_count() const {
  return page.read_int64(TUPLE_COUNT_OFFSET);
}

int64_t BucketPage::get_overflow_pointer() const {
  return page.read_int64(OVERFLOW_POINTER_OFFSET);
}

void BucketPage::set_tuple_count(int64_t new_tuple_count) {
  page.write_int64(TUPLE_COUNT_OFFSET, new_tuple_count);
}

void BucketPage::set_overflow_pointer(int64_t new_overflow_pointer) {
  page.write_int64(OVERFLOW_POINTER_OFFSET, new_overflow_pointer);
}

HashIndexRecord BucketPage::get_record(size_t pos) {
  size_t offset = HEADER_SIZE + pos * sizeof(HashIndexRecord);

  uint64_t hash = page.read_int64(offset);
  int32_t page_num = page.read_int32(offset + 8);
  int32_t dir_slot = page.read_int32(offset + 12);
  return HashIndexRecord(hash, RID(page_num, dir_slot));
}

void BucketPage::set_record(size_t slot, HashIndexRecord record) {
  size_t offset = HEADER_SIZE + slot * sizeof(HashIndexRecord);

  page.write_int64(offset, record.hash);
  page.write_int32(offset + 8, record.rid.page_num);
  page.write_int32(offset + 12, record.rid.dir_slot);
}

bool BucketPage::try_insert_record(uint64_t hash, RID rid) {
  size_t tuple_count = get_tuple_count();
  size_t insert_slot = tuple_count;

  if (insert_slot < MAX_VALUES_PER_BUCKET) {
    set_record(insert_slot, HashIndexRecord(hash, rid));
    set_tuple_count(tuple_count + 1);
    return true;
  }
  return false;
}

void BucketPage::delete_record(RID rid) {
  int pos = 0;

  while (pos < get_tuple_count()) {
    HashIndexRecord current = get_record(pos);

    if (current.rid == rid) {
      int last_index = get_tuple_count() - 1;

      if (pos != last_index) {
        HashIndexRecord last = get_record(last_index);
        set_record(pos, last);
      }

      set_tuple_count(last_index);

    } else {
      ++pos;
    }
  }
}
