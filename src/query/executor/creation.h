#pragma once

#include <string>
#include <iostream>

#include "query/executor/query_action.h"
#include "relational_model/schema.h"
#include "system/system.h"
#include "system/tx_id.h"

class Creation : public QueryAction {
public:
  Creation(const std::string& table_name, const Schema& schema, TxID tx_id)
      : tx_id(tx_id),
        table_name(table_name),
        schema(schema) {}

  void execute() override {
    catalog.create_table(table_name, schema, tx_id);
  }

  std::ostream& print_to_ostream(std::ostream& os, int indent = 0) const override {
    os << std::string(indent, ' ');
    os << "Creation(";
    os << table_name;
    for (size_t i = 0; i < schema.columns.size(); i++) {
      os << ", " << schema.columns[i].name << ":";
      if (schema.columns[i].datatype == DataType::STR) {
        os << "STR";
      } else {
        os << "INT";
      }
    }
    return os << ")\n";
  }

private:
  TxID tx_id;
  std::string table_name;
  Schema schema;
};
