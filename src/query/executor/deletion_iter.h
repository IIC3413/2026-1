#pragma once

#include <string>
#include <vector>

#include "query/executor/query_iter.h"
#include "relational_model/record.h"
#include "storage/heap_file/heap_file.h"
#include "system/system.h"

class DeletionIter : public QueryIter {
public:
  DeletionIter(std::unique_ptr<QueryIter> child, TxID tx_id)
      : child(std::move(child)),
        tx_id(tx_id) {}

  void begin() override {
    child->begin();
    delete_count = 0;
    columns = child->get_columns();
    size_t projected_rid_index = columns.size() - 1; // Last column of record is RID
    assert(columns[projected_rid_index].info.datatype == DataType::RID);
    table_name = columns[projected_rid_index].table;
  }

  Record next() override {
  begin_next:
    Record current_record = child->next();
    if (current_record.invalid()) {
      return Record();
    }
    const TableInfo* table_info = catalog.get_table_info(table_name, tx_id);
    auto first_rid = current_record.values.back().as_rid();
    lock_mgr.try_acquire_lock(tx_id, table_info->table_id, first_rid);

    bool valid = false;
    auto new_rid = table_info->heap_file->read(first_rid, tx_id, valid);
    if (!valid) {
      goto begin_next;
    }

    auto re_read_record = table_info->heap_file->get_record(new_rid);
    if (!child->matches(re_read_record)) {
      goto begin_next;
    } // row no longer satisfies WHERE
    catalog.delete_record(table_name, first_rid, tx_id);
    delete_count++;
    return current_record;
  }

  void reset() override {
    child->reset();
  }

  std::vector<Column> get_columns() override {
    return child->get_columns();
  }

  std::ostream& print_to_ostream(std::ostream& os, int indent = 0) const override {
    os << std::string(indent, ' ') << "DeletionIter(";
    bool first = true;
    for (const auto& col : child->get_columns()) {
      if (!first) {
        os << ", ";
      }
      os << col.info.name;
      first = false;
    }
    os << ")\n";
    return child->print_to_ostream(os, indent + 2);
  }

private:
  std::unique_ptr<QueryIter> child;
  std::vector<Column> columns;
  std::string table_name;
  TxID tx_id;
  int delete_count = 0;
};
