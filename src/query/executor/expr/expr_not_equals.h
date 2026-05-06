#pragma once

#include <memory>

#include "query/executor/expr/expr.h"

class ExprNotEquals : public Expr {
public:
  std::unique_ptr<Expr> lhs;

  std::unique_ptr<Expr> rhs;

  ExprNotEquals(std::unique_ptr<Expr> lhs, std::unique_ptr<Expr> rhs)
      : lhs(std::move(lhs)),
        rhs(std::move(rhs)),
        res((int64_t)0) {}

  Value eval(const Record& record) override {
    auto lhs_res = lhs->eval(record);
    auto rhs_res = rhs->eval(record);
    res.value = static_cast<int64_t>(lhs_res != rhs_res);
    return res;
  }

  std::ostream& print_to_ostream(std::ostream& os) const override {
    os << *lhs << " != " << *rhs;
    return os;
  }

private:
  Value res;
};
