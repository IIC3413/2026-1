#include "heap_file.h"

#include "storage/heap_file/heap_file_iter.h"
#include "storage/heap_file/heap_file_page.h"
#include "system/system.h"

HeapFile::HeapFile(const Schema& _schema, FileId file_id, TableId table_id)
    : schema(_schema),
      table_id(table_id),
      file_id(file_id) {
  for (auto& col : schema.columns) {
    col.table_id = table_id;
  }
  assert(!schema.columns.empty());
}

RID HeapFile::insert_record(const Record& record, TxID tx_id, std::optional<RID> first_rid) {
  auto current_page = std::make_unique<HeapFilePage>(*this, last_insert_page);
  RID res;
  // search block with available space and insert it there
  while (true) {
    if (current_page->try_insert_record(record, &res, tx_id, first_rid)) {
      return res;
    }
    last_insert_page++;
    current_page = std::make_unique<HeapFilePage>(*this, last_insert_page);
  }
}

RID HeapFile::get_last_version(const RID& rid) const {
  RID current_rid = rid;
  while (true) {
    auto page = std::make_unique<HeapFilePage>(*this, current_rid.page_num);
    const auto record_header = page->get_record_header(current_rid.dir_slot);
    RID next_rid = record_header.next;
    if (current_rid == next_rid) {
      break;
    } else {
      RID next_rid = record_header.next;
      current_rid = next_rid;
    }
    current_rid = next_rid;
  }
  return current_rid;
}

// update record managing versions and concurrency
RID HeapFile::update(RID rid, const Record& record, TxID tx_id) {
  const auto record_header_to_update = get_record_header(rid);

  if (record_header_to_update.is_invalid()) {
    return RID(-1, -2); // record deleted physically
  }
  RID to_update_rid = get_last_version(record_header_to_update.first);
  RID new_rid = insert_record(record, tx_id, record_header_to_update.first);

  HeapFilePage page(*this, to_update_rid.page_num);
  page.update_record_header(to_update_rid.dir_slot, new_rid, tx_id);

  return new_rid;
}

std::unique_ptr<HeapFileIter> HeapFile::get_record_iter(TxID tx_id) const {
  return std::make_unique<HeapFileIter>(*this, tx_id);
}

void HeapFile::delete_record(RID rid) {
  auto current_record_header = get_record_header(rid);
  if (current_record_header.is_invalid())
    return;
  auto page = std::make_unique<HeapFilePage>(*this, rid.page_num);
  page->delete_record_physically(rid.dir_slot);
  while (current_record_header.t_max != 0) {
    current_record_header = get_record_header(current_record_header.next);
    if (current_record_header.is_invalid()) {
      break;
    }
    page = std::make_unique<HeapFilePage>(*this, current_record_header.next.page_num);
    page->delete_record_physically(current_record_header.next.dir_slot);
  }
}

void HeapFile::vacuum() {
  auto total_pages = file_mgr.count_pages(file_id);

  for (auto i = 0; i < total_pages; i++) {
    HeapFilePage page(*this, i);
    page.vacuum();
  }
  last_insert_page = 0;
}

Record HeapFile::get_record(RID rid) const {
  HeapFilePage page(*this, rid.page_num);
  return page.get_record(rid.dir_slot);
}

RecordHeader HeapFile::get_record_header(RID rid) const {
  if (rid == RID(-1, -2)) {
    return RecordHeader();
  }
  HeapFilePage page(*this, rid.page_num);
  return page.get_record_header(rid.dir_slot);
}
