#pragma once

#include "query/parser/logical_plan/expr/expr_plan.h"
#include "relational_model/value.h"

class ExprPlanTerm : public ExprPlan {
public:
  Value value;

  ExprPlanTerm(Value&& value)
      : value(std::move(value)) {}

  std::unique_ptr<ExprPlan> clone() const override {
    auto value_copy = value;
    return std::make_unique<ExprPlanTerm>(std::move(value_copy));
  }

  void accept_visitor(ExprPlanVisitor& visitor) override {
    visitor.visit(*this);
  }

  DataType get_datatype() const override {
    if (value.is_string()) {
      return DataType::STR;
    }
    return DataType::INT;
  }

  std::set<Column> get_columns() const override {
    return {};
  }

  std::ostream& print_to_ostream(std::ostream& os) const override {
    os << value;
    return os;
  }
};
