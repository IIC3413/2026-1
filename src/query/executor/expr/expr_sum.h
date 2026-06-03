#pragma once

#include <memory>

#include "query/executor/expr/expr.h"

class ExprSum : public Expr {
public:
  std::unique_ptr<Expr> lhs;

  std::unique_ptr<Expr> rhs;

  ExprSum(std::unique_ptr<Expr> lhs, std::unique_ptr<Expr> rhs)
      : lhs(std::move(lhs)),
        rhs(std::move(rhs)) {}

  Value eval(const Record& record) override {
    auto lhs_res = lhs->eval(record);
    auto rhs_res = rhs->eval(record);
    return lhs_res + rhs_res;
  }

  std::ostream& print_to_ostream(std::ostream& os) const override {
    os << *lhs << " + " << *rhs;
    return os;
  }
};
