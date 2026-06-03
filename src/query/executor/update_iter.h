#pragma once

#include <string>
#include <vector>

#include "exceptions/exceptions.h"
#include "query/executor/expr/expr.h"
#include "query/executor/query_iter.h"
#include "relational_model/record.h"
#include "relational_model/value.h"
#include "storage/heap_file/heap_file.h"
#include "storage/heap_file/record_header.h"
#include "storage/rid.h"
#include "system/system.h"

class UpdateIter : public QueryIter {
public:
  UpdateIter(
      std::unique_ptr<QueryIter> child,
      std::vector<std::pair<size_t, std::unique_ptr<Expr>>>&& assignments,
      TxID tx_id
  )
      : child(std::move(child)),
        assignments(std::move(assignments)),
        tx_id(tx_id) {}

  void begin() override {
    child->begin();
    updated_count = 0;
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
    size_t rid_index = current_record.values.size() - 1; // Last column of record is RID
    Value first_rid_value = current_record.values[rid_index];
    assert(first_rid_value.is_rid());
    RID first_rid = first_rid_value.as_rid();

    auto table_info = catalog.get_table_info(table_name, tx_id);

    lock_mgr.try_acquire_lock(tx_id, table_info->table_id, first_rid);
    // add first_rid to write set so lock is released on early failure
    // transaction_mgr.add_to_write_set(table_info->table_id, first_rid, tx_id);

    const auto record_header = table_info->heap_file->get_record_header(first_rid);
    bool valid = false;
    // go to last commited version with the lock acquired and verify that it's deleted or not
    auto new_rid = table_info->heap_file->read(first_rid, tx_id, valid);
    if (!valid) {
      goto begin_next;
    }

    auto updated_record = table_info->heap_file->get_record(new_rid);
    if (!child->matches(updated_record)) {
      goto begin_next;
    }
    updated_record.values.push_back(Value(record_header.first)); // add RID to the end of record for update

    for (const auto& [col_index, new_value_expr] : assignments) {
      Value new_value = new_value_expr->eval(updated_record);
      if (new_value.is_int() && columns[col_index].info.datatype == DataType::INT) {
        updated_record.values[col_index] = new_value;
      } else if (new_value.is_string() && columns[col_index].info.datatype == DataType::STR) {
        updated_record.values[col_index] = new_value;
      } else {
        throw QueryException("Type mismatch in update assignment for column " + columns[col_index].info.name);
      }
    }
    catalog.update_record(table_name, first_rid, updated_record, tx_id);
    updated_count++;
    Record to_return_record = updated_record; // Remove RID from output
    assert(to_return_record.values.back().is_rid());
    to_return_record.values.pop_back();
    return to_return_record;
  }

  void reset() override {
    child->reset();
  }

  std::vector<Column> get_columns() override {
    return child->get_columns();
  }

  std::ostream& print_to_ostream(std::ostream& os, int indent = 0) const override {
    os << std::string(indent, ' ') << "UpdateIter(";
    bool first = true;
    auto columns = child->get_columns();
    for (const auto& [col_idx, val] : assignments) {
      if (!first)
        os << ", ";
      os << columns[col_idx].info.name << " = ";
      val->print_to_ostream(os);
      first = false;
    }
    os << ")\n";
    return child->print_to_ostream(os, indent + 2);
  }

private:
  std::unique_ptr<QueryIter> child;
  std::vector<std::pair<size_t, std::unique_ptr<Expr>>> assignments;
  std::vector<Column> columns;
  std::string table_name;
  TxID tx_id;
  int updated_count = 0;
};
