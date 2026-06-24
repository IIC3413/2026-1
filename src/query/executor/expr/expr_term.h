#pragma once

#include "query/executor/expr/expr.h"

class ExprTerm : public Expr {
public:
  ExprTerm(Value&& value)
      : res(std::move(value)) {}

  Value eval(const Record&) override {
    return res;
  }

  std::ostream& print_to_ostream(std::ostream& os) const override {
    os << res;
    return os;
  }

private:
  Value res;
};
