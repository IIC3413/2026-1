#pragma once

#include <memory>
#include <optional>

#include "relational_model/record.h"
#include "storage/file_id.h"
#include "storage/heap_file/heap_file_iter.h"
#include "storage/heap_file/record_header.h"
#include "storage/rid.h"
#include "system/tx_id.h"

// Logical deletion: when a record is deleted by a commited transaction, we set t_max to the transaction id
// that deleted it and we set next RID to (-1, -1)
// Physical deletion: when the dir slot is marked as -2
class HeapFile {
public:
  Schema schema;

  TableId table_id;

  const FileId file_id;

  HeapFile(const Schema& schema, FileId file_id, TableId table_id);

  // inserts a new record
  RID insert_record(const Record& record, TxID tx_id, std::optional<RID> first_rid = std::nullopt);

  void delete_record(RID rid, TxID tx_id);

  // update record at rid with record managing versions, concurrency and locks.
  RID update(RID rid, const Record& record, TxID tx_id);

  // Iterates over all results
  std::unique_ptr<HeapFileIter> get_record_iter(TxID tx_id) const;

  Record get_record(RID rid) const;

  RecordHeader get_record_header(RID rid) const;

  // read and write doesn't exist for lab 1.
  // gives last visible version
  // valid is false if the record is not visible or doesn't exist
  RID read(RID rid, TxID tx_id, bool& valid) const;

  void undo(RID first_rid, TxID tx_id);

  bool is_visible(const RecordHeader& record_header, TxID tx_id) const;

  RID get_last_version(const RID& rid) const;

  void vacuum(); // for lab1 clean all less first and last

  void full_vacuum();

private:
  // remembers where was the last insert so it doesn't begin from the start the next time
  std::atomic<int64_t> last_insert_page = 0;
};
