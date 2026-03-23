#include "heap_file_page.h"

#include "relational_model/record.h"
#include "storage/heap_file/heap_file.h"
#include "storage/heap_file/record_header.h"
#include "storage/page.h"
#include "storage/rid.h"
#include "system/system.h"

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

RID HeapFilePage::get_next_RID(int32_t dir_pos) const {
  auto record_offset = get_dir(dir_pos);
  if (record_offset <= 0) {
    return RID(-1, -2);
  }
  int32_t next_page = page.read_int32(record_offset + NEXT_RID_PAGE_OFFSET);
  int32_t next_dir = page.read_int32(record_offset + NEXT_RID_DIR_OFFSET);
  return RID(next_page, next_dir);
}

RecordHeader HeapFilePage::get_record_header(int32_t dir_pos) const {
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
  std::lock_guard<std::mutex> guard(insert_mutex);
  set_dir(dir_pos, -2);
}

bool HeapFilePage::try_insert_record(
    const Record& record, RID* out_rid, TxID tx_id, std::optional<RID> first_rid
) {
  std::lock_guard<std::mutex> guard(insert_mutex);
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
  //TODO: Lab 1
  // Hint: missing add the record header to needed_record_size
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
  std::lock_guard<std::mutex> guard(insert_mutex);
  set_tmax(dir_pos, tx_id);
  set_next_RID(dir_pos, new_rid);
}

void HeapFilePage::vacuum() {
  char* page_buf = new char[Page::SIZE];
  //TODO: Lab 1
  delete[] page_buf;
}
