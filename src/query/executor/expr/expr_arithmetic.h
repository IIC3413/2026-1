#pragma once

#include <memory>

#include "query/executor/expr/expr.h"

class ExprArithmetic : public Expr {
public:
  std::unique_ptr<Expr> lhs;

  std::string operator_;

  std::unique_ptr<Expr> rhs;

  ExprArithmetic(std::unique_ptr<Expr> lhs, std::string operator_, std::unique_ptr<Expr> rhs)
      : lhs(std::move(lhs)),
        operator_(std::move(operator_)),
        rhs(std::move(rhs)) {}

  Value eval(const Record& record) override {
    auto lhs_res = lhs->eval(record);
    auto rhs_res = rhs->eval(record);
    if (operator_ == "+") {
      return lhs_res + rhs_res;
    } else if (operator_ == "-") {
      return lhs_res - rhs_res;
    } else if (operator_ == "*") {
      return lhs_res * rhs_res;
    } else if (operator_ == "/") {
      return lhs_res / rhs_res;
    } else if (operator_ == "%") {
      return lhs_res % rhs_res;
    } else {
      throw std::runtime_error("Unsupported operator: " + operator_);
    }
  }

  std::ostream& print_to_ostream(std::ostream& os) const override {
    os << *lhs << " " << operator_ << " " << *rhs;
    return os;
  }
};
