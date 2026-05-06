#pragma once

#include <string>
#include <iostream>

#include "query/executor/query_action.h"
#include "system/system.h"
#include "system/tx_id.h"

class IndexCreation : public QueryAction {
public:
  IndexCreation(const std::string& table_name, const std::string& column_name, TxID tx_id)
      : tx_id(tx_id),
        table_name(table_name),
        column_name(column_name) {}

  void execute() override {
    catalog.create_index(table_name, column_name, tx_id);
  }

  std::ostream& print_to_ostream(std::ostream& os, int indent = 0) const override {
    os << std::string(indent, ' ');
    os << "IndexCreation(";
    os << table_name;
    os << ", " << column_name;
    return os << ")\n";
  }

private:
  TxID tx_id;
  std::string table_name;
  std::string column_name;
};
