#include "heap_file_iter.h"

#include "storage/heap_file/heap_file.h"
#include "storage/heap_file/heap_file_page.h"
#include "system/system.h"

HeapFileIter::HeapFileIter(const HeapFile& heap_file, TxID tx_id)
    : heap_file(heap_file),
      tx_id(tx_id) {
  // value starts as -1 because in next we always sum 1 before processing
  current_page_record_pos = -1;

  current_page_number = 0;
  current_page = std::make_unique<HeapFilePage>(heap_file, 0);
  total_pages = file_mgr.count_pages(heap_file.file_id);
}

void HeapFileIter::begin() {
  // Don't need to prepare anything
}

Record HeapFileIter::next() {

  while (current_page != nullptr) {
    current_page_record_pos++;
    // static_cast in not necessary, only to avoid a warning
    if (current_page_record_pos >= static_cast<int64_t>(current_page->get_dir_count())) {
      current_page_record_pos = -1;
      current_page_number++;

      if (current_page_number < total_pages) {
        current_page = std::make_unique<HeapFilePage>(heap_file, current_page_number);
        continue;
      } else {
        current_page = nullptr;
        return Record();
      }
    }
    RID current_rid(current_page_number, current_page_record_pos);
    const auto current_record = heap_file.get_record_header(current_rid);
    if (current_record.is_invalid()) { // only if delete is physical
      continue;
    }
    if (RID(current_page_number, current_page_record_pos) == current_record.first) {
      auto new_rid = heap_file.get_last_version(current_rid);
      if (new_rid == RID(-1, -2)) {
        continue;
      }
      auto record = heap_file.get_record(new_rid);
      if (!record.invalid()) {
        record.values.push_back(Value(current_record.first)); // add RID to the end of record for update
        return record;
      }
    }
  }
  return Record();
}

void HeapFileIter::reset() {
  current_page_record_pos = -1;
  current_page_number = 0;
  current_page = std::make_unique<HeapFilePage>(heap_file, 0);
}

RID HeapFileIter::get_current_RID() const {
  return RID(current_page_number, current_page_record_pos);
}
