#pragma once

#include "query/parser/logical_plan/logical_plan.h"
#include "query/parser/logical_plan/logical_plan_visitor.h"
#include "query/parser/logical_plan/expr/expr_plan.h"
#include "relational_model/table_info.h"
#include "query/parser/query_preprocessor/query_preprocessor.h"
#include "relational_model/schema.h"
#include <map>
#include <memory>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

class UpdatePlan : public LogicalPlan {
public:
  const TableInfo& table_info;
  std::vector<std::pair<int, std::unique_ptr<ExprPlan>>> update_values;
  std::unique_ptr<LogicalPlan> child; // Optional WHERE condition or relation
  UpdatePlan(
      const TableInfo& table_info,
      std::vector<std::pair<int, std::unique_ptr<ExprPlan>>>&& update_values,
      std::unique_ptr<LogicalPlan>&& child = nullptr
  )
      : table_info(table_info),
        update_values(std::move(update_values)),
        child(std::move(child)) {}

  void accept_visitor(LogicalPlanVisitor& visitor) override {
    visitor.visit(*this);
  }

  std::unique_ptr<LogicalPlan> clone() const override {
    std::vector<std::pair<int, std::unique_ptr<ExprPlan>>> update_values_clone;
    std::unique_ptr<LogicalPlan> child_clone = child ? child->clone() : nullptr;
    return std::make_unique<UpdatePlan>(table_info, std::move(update_values_clone), std::move(child_clone));
  }

  bool is_action() const override {
    return true;
  }

  std::ostream& print_to_ostream(std::ostream& os, int indent = 0) const override {
    os << std::string(indent, ' ') << "Update(" << table_info.name << ", SET ";
    bool first = true;
    for (const auto& [column_idx, expr] : update_values) {
      if (!first) {
        os << ", ";
      }
      os << table_info.schema->columns[column_idx].name << " = " << *expr;
      first = false;
    }
    os << ")";
    if (child != nullptr) {
      os << "\n";
      child->print_to_ostream(os, indent + 2);
    }
    return os;
}

};
