#pragma once

#include <cstdint>
#include <mutex>
#include <optional>

#include "relational_model/record.h"
#include "storage/heap_file/record_header.h"
#include "storage/page.h"
#include "storage/rid.h"
#include "system/tx_id.h"

// Logical deletion: when a record is deleted by a commited transaction, we set t_max to the transaction id
// that deleted it and we set next RID to (-1, -1)
// Physical deletion: when the dir slot is marked as -2

class HeapFile;

class HeapFilePage {
public:
  static constexpr int32_t HEADER_SIZE = 8;
  static constexpr int32_t DIR_SIZE = 4;           // bytes per directory entry
  static constexpr int32_t TUPLE_HEADER_SIZE = 32; // bytes per tuple header

  // The tuple header contains the following:
  static constexpr int32_t TMIN_OFFSET = 0;
  static constexpr int32_t TMAX_OFFSET = 8;
  static constexpr int32_t NEXT_RID_PAGE_OFFSET = 16;
  static constexpr int32_t NEXT_RID_DIR_OFFSET = 20;
  static constexpr int32_t FIRST_RID_PAGE_OFFSET = 24;
  static constexpr int32_t FIRST_RID_DIR_OFFSET = 28;

  const HeapFile& heap_file;

  Page& page;

  HeapFilePage(const HeapFile& heap_file, int64_t page_number);

  ~HeapFilePage();

  // returns true if record was inserted, false if no space available
  // when the function returns true, the out_record_id is setted
  bool try_insert_record(const Record& record, RID* out_rid, TxID tx_id, std::optional<RID> first_rid);

  void vacuum();

  // returns record with empty vector if dir_pos is marked as deleted
  Record get_record(int32_t dir_pos) const;

  RecordHeader get_record_header(int32_t dir_pos) const;

  void delete_record_physically(int32_t dir_pos);

  int32_t get_dir_count() const;

  int32_t get_free_space() const;

  int32_t get_dir(int32_t idx) const;

  int64_t get_tmin(int32_t dir_pos) const;

  int64_t get_tmax(int32_t dir_pos) const;

  RID get_next_RID(int32_t dir_pos) const;

  void update_record_header(int32_t dir_pos, RID new_rid, TxID tx_id);

private:
  void set_dir_count(int32_t new_dir_count);

  void set_tmax(int32_t dir_pos, int64_t new_tmax);

  void set_next_RID(int32_t dir_pos, RID new_rid);

  void set_free_space(int32_t new_free_space);

  void set_dir(int32_t idx, int32_t new_dir_value);

  void set_first_RID(int32_t dir_pos, RID first_rid);

  TableId table_id;

  std::mutex insert_mutex;
};
