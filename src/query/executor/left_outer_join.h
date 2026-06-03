#pragma once

#include <cassert>

#include "query/executor/query_iter.h"
#include "relational_model/schema.h"

class LeftOuterJoin : public QueryIter {
public:
  LeftOuterJoin(
      std::unique_ptr<QueryIter> _lhs,
      std::unique_ptr<QueryIter> _rhs,
      std::vector<ProjectedColumn>&& _projected_lhs_columns,
      std::vector<ProjectedColumn>&& _projected_rhs_columns,
      std::vector<std::pair<size_t, size_t>>&& _equalities
  )
      : lhs(std::move(_lhs)),
        rhs(std::move(_rhs)),
        projected_lhs_columns(std::move(_projected_lhs_columns)),
        projected_rhs_columns(std::move(_projected_rhs_columns)),
        equalities(std::move(_equalities)) {
    assert(equalities.size() > 0);
    init_rhs_null();
    init_refs();
  }

  void begin() override {
    lhs->begin();
    rhs->begin();
    valid_lhs = false;
  }

  Record next() override {
    while (true) {
      if (!valid_lhs) {
        current_lhs = lhs->next();
        if (current_lhs.invalid()) {
          return Record();
        }
        outer_match = false;
        valid_lhs = true;
        rhs->reset();
      }

      current_rhs = rhs->next();
      while (!current_rhs.invalid()) {
        bool inner_match = true;
        for (const auto& eq : equalities) {
          if (current_lhs.values[eq.first] != current_rhs.values[eq.second]) {
            inner_match = false;
            break;
          }
        }
        if (inner_match) {
          std::vector<Value> combined_values;
          combined_values.reserve(projected_lhs_columns.size() + projected_rhs_columns.size());
          for (size_t i = 0; i < projected_lhs_columns.size(); i++) {
            combined_values.push_back(current_lhs.values[projected_lhs_columns[i].pos]);
          }
          for (size_t i = 0; i < projected_rhs_columns.size(); i++) {
            combined_values.push_back(current_rhs.values[projected_rhs_columns[i].pos]);
          }
          outer_match = true;
          return Record(combined_values);
        }
        current_rhs = rhs->next();
      }

      valid_lhs = false;
      if (!outer_match) {
        std::vector<Value> combined_values;
        combined_values.reserve(projected_lhs_columns.size() + projected_rhs_columns.size());
        for (size_t i = 0; i < projected_lhs_columns.size(); i++) {
          combined_values.push_back(current_lhs.values[projected_lhs_columns[i].pos]);
        }
        for (size_t i = 0; i < projected_rhs_columns.size(); i++) {
          combined_values.push_back(rhs_null_values[projected_rhs_columns[i].pos]);
        }
        return Record(combined_values);
      }
    }
    return Record();
  }

  void reset() override {
    lhs->reset();
    rhs->reset();
    valid_lhs = false;
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
    os << "LeftOuterJoin (";
    os << projected_lhs_columns[equalities[0].first].col.alias << "."
       << projected_lhs_columns[equalities[0].first].col.info.name;
    os << " == ";
    os << projected_rhs_columns[equalities[0].second].col.alias << "."
       << projected_rhs_columns[equalities[0].second].col.info.name;
    for (size_t i = 1; i < equalities.size(); ++i) {
      os << " AND ";
      os << projected_lhs_columns[equalities[i].first].col.alias << "."
         << projected_lhs_columns[equalities[i].first].col.info.name;
      os << " == ";
      os << projected_rhs_columns[equalities[i].second].col.alias << "."
         << projected_rhs_columns[equalities[i].second].col.info.name;
    }
    os << ")\n";
    lhs->print_to_ostream(os, indent + 2);
    rhs->print_to_ostream(os, indent + 2);
    return os;
  }

private:
  std::unique_ptr<QueryIter> lhs;
  std::unique_ptr<QueryIter> rhs;

  std::vector<ProjectedColumn> projected_lhs_columns;
  std::vector<ProjectedColumn> projected_rhs_columns;

  std::vector<std::pair<size_t, size_t>> equalities;

  Record current_lhs;
  Record current_rhs;

  std::unique_ptr<Record> rhs_buffer;

  bool valid_lhs;
  bool outer_match;

  std::vector<Value> rhs_null_values;

  void init_refs() {
    std::vector<DataType> rhs_datatypes;
    for (auto& rhs_projected_column : projected_rhs_columns) {
      rhs_datatypes.push_back(rhs_projected_column.col.info.datatype);
    }
    rhs_buffer = std::make_unique<Record>(std::move(rhs_datatypes));
  }

  void init_rhs_null() {
    for (const auto& c : projected_rhs_columns) {
      switch (c.col.info.datatype) {
      case DataType::RID:
      case DataType::INVALID:
        break;
      case DataType::INT:
        rhs_null_values.push_back(Value(-1));
        break;
      case DataType::STR:
        rhs_null_values.push_back(Value("-1"));
        break;
      }
    }
  }
};
