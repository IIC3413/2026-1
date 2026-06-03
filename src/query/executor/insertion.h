#pragma once

#include <cstdint>
#include <variant>
#include <vector>

#include "query/executor/query_action.h"
#include "query/parser/query_preprocessor/query_preprocessor.h"
#include "system/system.h"

class Insertion : public QueryAction {
public:
  Insertion(const std::string& _table, std::vector<Constant>&& _values, TxID tx_id)
      : table(_table),
        values(_values),
        tx_id(tx_id) {}

  void execute() override {
    std::vector<Value> insert_values;
    for (const auto& val : values) {
      if (std::holds_alternative<int64_t>(val)) {
        insert_values.push_back(Value(std::get<int64_t>(val)));
      } else {
        insert_values.push_back(Value(std::get<std::string>(val)));
      }
    }
    catalog.insert_record(table, std::move(insert_values), tx_id);
  }

  std::ostream& print_to_ostream(std::ostream& os, int indent = 0) const override {
    os << std::string(indent, ' ');
    os << "Insertion(";
    os << table;
    for (size_t i = 0; i < values.size(); i++) {
      if (std::holds_alternative<int64_t>(values[i])) {
        os << ", " << std::get<int64_t>(values[i]);
      } else {
        os << ", " << std::get<std::string>(values[i]);
      }
    }
    return os << ")\n";
  }

private:
  std::string table;
  std::vector<Constant> values;
  TxID tx_id;
};
