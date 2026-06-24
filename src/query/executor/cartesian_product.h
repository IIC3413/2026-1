#pragma once

#include "query/executor/query_iter.h"

class CartesianProduct : public QueryIter {
public:
  CartesianProduct(
      std::unique_ptr<QueryIter> _lhs,
      std::unique_ptr<QueryIter> _rhs,
      std::vector<ProjectedColumn>&& _projected_lhs_columns,
      std::vector<ProjectedColumn>&& _projected_rhs_columns
  )
      : lhs(std::move(_lhs)),
        rhs(std::move(_rhs)),
        projected_lhs_columns(std::move(_projected_lhs_columns)),
        projected_rhs_columns(std::move(_projected_rhs_columns)) {}

  void begin() override {
    lhs->begin();
    rhs->begin();

    valid_lhs = false;
  }

  // simple nested loop join
  Record next() override {
    while (true) {
      if (valid_lhs) {
        current_rhs = rhs->next();
        if (!current_rhs.invalid()) {
          std::vector<Value> combined_values;
          combined_values.reserve(projected_lhs_columns.size() + projected_rhs_columns.size());
          for (size_t i = 0; i < projected_lhs_columns.size(); i++) {
            combined_values.push_back(current_lhs.values[projected_lhs_columns[i].pos]);
          }
          for (size_t i = 0; i < projected_rhs_columns.size(); i++) {
            combined_values.push_back(current_rhs.values[projected_rhs_columns[i].pos]);
          }
          return Record(combined_values);
        } else {
          valid_lhs = false;
        }
      } else {
        current_lhs = lhs->next();
        if (!current_lhs.invalid()) {
          valid_lhs = true;
          rhs->reset();
        } else {
          return Record();
        }
      }
    }
    return Record();
  }

  void reset() override {
    lhs->reset();
    rhs->reset();
  }

  std::vector<Column> get_columns() override {
    std::vector<Column> res;
    for (auto& c : projected_lhs_columns) {
      res.push_back(c.col);
    }
    for (auto& c : projected_rhs_columns) {
      res.push_back(c.col);
    }
    return res;
  }

  std::ostream& print_to_ostream(std::ostream& os, int indent = 0) const override {
    os << std::string(indent, ' ');
    os << "CartesianProduct()\n";
    lhs->print_to_ostream(os, indent + 2);
    rhs->print_to_ostream(os, indent + 2);
    return os;
  }

private:
  std::unique_ptr<QueryIter> lhs;
  std::unique_ptr<QueryIter> rhs;
  std::vector<ProjectedColumn> projected_lhs_columns;
  std::vector<ProjectedColumn> projected_rhs_columns;
  Record current_lhs;
  Record current_rhs;
  bool valid_lhs;
};
