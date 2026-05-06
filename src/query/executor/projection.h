#pragma once

#include "query/executor/query_iter.h"

class Projection : public QueryIter {
public:
  Projection(std::unique_ptr<QueryIter> _child, std::vector<Column> _projected_columns, uint64_t _limit)
      : child(std::move(_child)),
        projected_columns(std::move(_projected_columns)),
        limit(_limit) {}

  void begin() override {
    result_count = 0;
    child->begin();
  }

  Record next() override {
    Record current_tuple = child->next();
    if (current_tuple.invalid() || result_count >= limit) {
      return Record();
    }
    result_count++;

    std::vector<Value> projected_tuple;
    projected_tuple.reserve(projected_columns.size());
    for (size_t i = 0; i < projected_columns.size(); i++) {
      for (size_t j = 0; j < child->get_columns().size(); j++) {
        if (child->get_columns()[j] == projected_columns[i]) {
          projected_tuple.push_back(current_tuple.values[j]);
          break;
        }
      }
    }
    return Record(std::move(projected_tuple));
  }

  void reset() override {
    result_count = 0;
    child->reset();
  }

  std::vector<Column> get_columns() override {
    return projected_columns;
  }

  std::ostream& print_to_ostream(std::ostream& os, int indent = 0) const override {
    os << std::string(indent, ' ');
    os << "Projection(";
    os << projected_columns[0].alias << "." << projected_columns[0].info.name;
    for (size_t i = 1; i < projected_columns.size(); i++) {
      os << ", " << projected_columns[i].alias << "." << projected_columns[i].info.name;
    }
    os << ")\n";
    child->print_to_ostream(os, indent + 2);
    return os;
  }

private:
  std::unique_ptr<QueryIter> child;
  std::vector<Column> projected_columns;
  const uint64_t limit;
  uint64_t result_count;
};
