#include "heap_file_page.h"

#include "relational_model/record.h"
#include "storage/heap_file/heap_file.h"
#include "storage/heap_file/record_header.h"
#include "storage/page.h"
#include "storage/rid.h"
#include "system/system.h"

#include <mutex>

HeapFilePage::HeapFilePage(const HeapFile& heap_file, int64_t page_number)
    : heap_file(heap_file),
      page(buffer_mgr.get_page(heap_file.file_id, page_number)) {
  // if new page, initialize to be valid
  // new pages comes with all bytes setted at 0
  if (get_dir_count() == 0 && get_free_space() == 0) {
    set_free_space(Page::SIZE - 2 * sizeof(int32_t));
  }
  table_id = heap_file.table_id;
}

HeapFilePage::~HeapFilePage() {
  page.unpin();
}

void HeapFilePage::set_dir_count(int32_t new_dir_count) {
  page.write_int32(0, new_dir_count);
}

void HeapFilePage::set_free_space(int32_t new_free_space) {
  page.write_int32(4, new_free_space);
}

void HeapFilePage::set_dir(int32_t idx, int32_t new_dir_value) {
  int offset = HEADER_SIZE + DIR_SIZE * idx;
  page.write_int32(offset, new_dir_value);
}

void HeapFilePage::set_first_RID(int32_t dir_pos, const RID first_rid) {
  int32_t record_offset = get_dir(dir_pos);
  page.write_int32(record_offset + FIRST_RID_PAGE_OFFSET, first_rid.page_num);
  page.write_int32(record_offset + FIRST_RID_DIR_OFFSET, first_rid.dir_slot);
}

int32_t HeapFilePage::get_dir_count() const {
  return page.read_int32(0);
}

int32_t HeapFilePage::get_free_space() const {
  return page.read_int32(4);
}

int32_t HeapFilePage::get_dir(int32_t idx) const {
  return page.read_int32(HEADER_SIZE + DIR_SIZE * idx);
}

int64_t HeapFilePage::get_tmin(int32_t dir_pos) const {
  auto record_offset = get_dir(dir_pos);
  return page.read_int64(record_offset + TMIN_OFFSET);
}

int64_t HeapFilePage::get_tmax(int32_t dir_pos) const {
  auto record_offset = get_dir(dir_pos);
  return page.read_int64(record_offset + TMAX_OFFSET);
}

// RID HeapFilePage::get_next_RID(int32_t dir_pos) const {
//   auto record_offset = get_dir(dir_pos);
//   if (record_offset <= 0) {
//     return RID(-1, -2);
//   }
//   int32_t next_page = page.read_int32(record_offset + NEXT_RID_PAGE_OFFSET);
//   int32_t next_dir = page.read_int32(record_offset + NEXT_RID_DIR_OFFSET);
//   return RID(next_page, next_dir);
// }

bool HeapFilePage::is_page_empty() const {
  for (int32_t i = 0; i < get_dir_count(); i++) {
    if (get_dir(i) >= 0) {
      return false;
    }
  }
  return true;
}

RecordHeader HeapFilePage::get_record_header(int32_t dir_pos) const {
  std::shared_lock guard(page.edit_mutex);
  auto offset = get_dir(dir_pos);

  if (offset <= 0) {
    return RecordHeader();
  }

  int64_t tmin = page.read_int64(offset + TMIN_OFFSET);
  int64_t tmax = page.read_int64(offset + TMAX_OFFSET);

  int32_t next_page = page.read_int32(offset + NEXT_RID_PAGE_OFFSET);
  int32_t next_dir = page.read_int32(offset + NEXT_RID_DIR_OFFSET);

  int32_t first_page = page.read_int32(offset + FIRST_RID_PAGE_OFFSET);
  int32_t first_dir = page.read_int32(offset + FIRST_RID_DIR_OFFSET);

  RID first_rid(first_page, first_dir);
  RID next(next_page, next_dir);

  return RecordHeader(tmin, tmax, next, first_rid);
}

Record HeapFilePage::get_record(int32_t dir_pos) const {
  std::shared_lock guard(page.edit_mutex);
  auto offset = get_dir(dir_pos);

  if (offset <= 0) {
    return Record();
  }

  offset += TUPLE_HEADER_SIZE;

  std::vector<Value> values;

  // read record data
  for (auto& col : heap_file.schema.columns) {
    switch (col.datatype) {
    case DataType::INT: {
      values.push_back(page.read_int64(offset));
      offset += sizeof(int64_t);
      break;
    }
    case DataType::STR: {
      uint8_t len = page.read_uint8(offset);
      offset += 1;

      std::string s;
      s.resize(len);
      page.read(offset, len, s.data());

      offset += len;

      values.push_back(s);
      break;
    }
    case DataType::RID: {
      break;
    }
    case DataType::INVALID:
      break;
    }
  }

  return Record(std::move(values));
}

Record HeapFilePage::_get_record(int32_t dir_pos) const {
  auto offset = get_dir(dir_pos);

  if (offset <= 0) {
    return Record();
  }

  offset += TUPLE_HEADER_SIZE;

  std::vector<Value> values;

  // read record data
  for (auto& col : heap_file.schema.columns) {
    switch (col.datatype) {
    case DataType::INT: {
      values.push_back(page.read_int64(offset));
      offset += sizeof(int64_t);
      break;
    }
    case DataType::STR: {
      uint8_t len = page.read_uint8(offset);
      offset += 1;

      std::string s;
      s.resize(len);
      page.read(offset, len, s.data());

      offset += len;

      values.push_back(s);
      break;
    }
    case DataType::RID: {
      break;
    }
    case DataType::INVALID:
      break;
    }
  }

  return Record(std::move(values));
}

void HeapFilePage::delete_record_physically(int32_t dir_pos) {
  std::lock_guard guard(page.edit_mutex);
  set_dir(dir_pos, -2); // mark the directory entry as deleted, so vacuum can clean it up
}

void HeapFilePage::delete_record_logically(int32_t dir_pos, TxID tx_id) {
  std::lock_guard guard(page.edit_mutex);
  set_tmax(dir_pos, tx_id);
  set_next_RID(dir_pos, RID(-1, -1)); // mark as deleted the last version of the tuple
}

bool HeapFilePage::try_insert_record(
    const Record& record, RID* out_rid, TxID tx_id, std::optional<RID> first_rid
) {
  std::lock_guard guard(page.edit_mutex);
  int32_t needed_record_size = 0; // Directory entry size
  for (size_t i = 0; i < record.values.size(); i++) {
    const auto& value = record.values[i];

    if (value.is_string()) {
      needed_record_size += 1 + value.as_string().size();
    } else if (value.is_int()) {
      needed_record_size += sizeof(int64_t);
    }
  }

  int32_t dir_pos = 0;
  auto dir_count = get_dir_count();
  while (dir_pos < dir_count && get_dir(dir_pos) > 0) {
    dir_pos++;
  }

  auto free_space = get_free_space();

  if (dir_pos < dir_count) { // found dir to reuse
    if (free_space < needed_record_size + TUPLE_HEADER_SIZE) {
      return false;
    }
    free_space -= needed_record_size + TUPLE_HEADER_SIZE;
  } else { // dir_pos == dir_count
    if (free_space < needed_record_size + TUPLE_HEADER_SIZE + DIR_SIZE) {
      return false;
    }
    dir_count++;
    set_dir_count(dir_count);
    free_space -= needed_record_size + TUPLE_HEADER_SIZE + DIR_SIZE;
  }
  set_free_space(free_space);

  int32_t offset = HEADER_SIZE + DIR_SIZE * dir_count + free_space;
  set_dir(dir_pos, offset);

  *out_rid = RID(page.page_id.page_number, dir_pos);

  // write tuple header
  page.write_int64(offset + TMIN_OFFSET, tx_id); // t_min
  page.write_int64(offset + TMAX_OFFSET, 0);     // t_max

  page.write_int32(offset + NEXT_RID_PAGE_OFFSET, page.page_id.page_number);    // next RID page
  page.write_int32(offset + NEXT_RID_DIR_OFFSET, dir_pos);                      // next RID dir
  if (first_rid == std::nullopt) {                                              // first version
    page.write_int32(offset + FIRST_RID_PAGE_OFFSET, page.page_id.page_number); // first RID page
    page.write_int32(offset + FIRST_RID_DIR_OFFSET, dir_pos);                   // first RID dir
  } else {                                                                      // update version
    page.write_int32(offset + FIRST_RID_PAGE_OFFSET, first_rid->page_num);      // first RID page
    page.write_int32(offset + FIRST_RID_DIR_OFFSET, first_rid->dir_slot);       // first RID dir
  }
  offset += TUPLE_HEADER_SIZE;

  // write record data
  for (auto& value : record.values) {
    if (value.is_string()) {
      auto str = value.as_string();
      uint8_t len = str.size();
      page.write_int8(offset, len);
      offset += 1;

      page.write(offset, len, str.data());
      offset += len;
    } else if (value.is_int()) {
      page.write_int64(offset, value.as_int());
      offset += sizeof(int64_t);
    }
  }
  return true;
}

void HeapFilePage::set_tmax(int32_t dir_pos, int64_t new_tmax) {
  int32_t record_offset = get_dir(dir_pos);
  page.write_int64(record_offset + TMAX_OFFSET, new_tmax);
}

void HeapFilePage::set_next_RID(int32_t dir_pos, RID new_rid) {
  int32_t record_offset = get_dir(dir_pos);
  page.write_int32(record_offset + NEXT_RID_PAGE_OFFSET, new_rid.page_num);
  page.write_int32(record_offset + NEXT_RID_DIR_OFFSET, new_rid.dir_slot);
}

void HeapFilePage::update_record_header(int32_t dir_pos, RID new_rid, TxID tx_id) {
  std::lock_guard guard(page.edit_mutex);
  set_tmax(dir_pos, tx_id);
  set_next_RID(dir_pos, new_rid);
}

void HeapFilePage::reset_update(int32_t dir_pos) {
  std::lock_guard guard(page.edit_mutex);
  set_tmax(dir_pos, 0);
  set_next_RID(dir_pos, RID(page.page_id.page_number, dir_pos));
}

void HeapFilePage::reset_first(int32_t dir_pos) {
  std::lock_guard guard(page.edit_mutex);
  set_first_RID(dir_pos, RID(page.page_id.page_number, dir_pos));
}

void HeapFilePage::vacuum() {
  std::lock_guard guard(page.edit_mutex);

  // Reuse space of directory entries marked as -2.
  // Transaction tx = transaction_mgr.start_transaction(IsolationLevel::READ_COMMITTED);
  // for (int32_t actual_dir = 0; actual_dir < get_dir_count(); actual_dir++) {
  //   const auto record_header = get_record_header(actual_dir);
  //   if (record_header.is_invalid()) {
  //     RID rid(page.page_id.page_number, actual_dir);
  //     lock_mgr.try_acquire_lock(tx.get_id(), table_id, rid);
  //     // transaction_mgr.add_to_write_set(table_id, rid, tx.get_id());
  //   } else {
  //     lock_mgr.try_acquire_lock(tx.get_id(), table_id, record_header.first);
  //     // transaction_mgr.add_to_write_set(table_id, record_header.first, tx.get_id());
  //   }
  // }
  // // ASSUMPTION: We get all locks needed for the page.
  char* page_buf = new char[Page::SIZE];

  int32_t dir_count = 0;
  int32_t last_useful_dir_count = 0;
  int32_t free_space = Page::SIZE - HEADER_SIZE;
  auto dirs = reinterpret_cast<int32_t*>(page_buf + HEADER_SIZE);

  for (int32_t i = 0; i < get_dir_count(); i++) {
    // we maintain the RID of the non deleted records
    free_space -= DIR_SIZE;
    if (get_dir(i) < 0) {
      dirs[i] = -1;
      dir_count++;
      continue;
    } else {
      last_useful_dir_count = dir_count;
    }

    int32_t record_size = TUPLE_HEADER_SIZE;

    // vacuum() already owns edit_mutex, so we call _get_record()
    // to avoid locking the same mutex again
    for (auto& value : _get_record(i).values) {
      if (value.is_string()) {
        record_size += 1 + value.as_string().size();
      } else if (value.is_int()) {
        record_size += sizeof(int64_t);
      }
    }

    dir_count += 1;
    free_space -= record_size;

    auto offset = HEADER_SIZE + DIR_SIZE * dir_count + free_space;
    dirs[dir_count - 1] = offset;
    page.read(get_dir(i), record_size, page_buf + offset);
  }

  last_useful_dir_count++;
  free_space += (dir_count - last_useful_dir_count) * DIR_SIZE;
  dir_count = last_useful_dir_count;

  page.write(0, Page::SIZE, page_buf);
  page.write_int32(0, dir_count);
  page.write_int32(4, free_space);
  delete[] page_buf;

  // transaction_mgr.commit_transaction(tx.get_id());
}
