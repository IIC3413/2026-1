#pragma once

#include "query/executor/expr/expr.h"
#include "query/parser/logical_plan/logical_plan.h"

class ExprColumn : public Expr {
public:
  ExprColumn(Column column, int record_pos)
      : column(column),
        record_pos(record_pos) {}

  Value eval(const Record& record) override {
    return record.values[record_pos];
  }

  std::ostream& print_to_ostream(std::ostream& os) const override {
    os << column.alias << "." << column.info.name;
    return os;
  }

private:
  Column column;
  int record_pos;
};
