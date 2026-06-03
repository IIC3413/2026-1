#pragma once

#include <memory>
#include <ostream>
#include <string>
#include <utility>

#include "query/parser/logical_plan/logical_plan.h"
#include "query/parser/logical_plan/logical_plan_visitor.h"
#include "relational_model/table_info.h"

class DeletionPlan : public LogicalPlan {
public:
  const TableInfo& table_info;
  std::unique_ptr<LogicalPlan> child;

  DeletionPlan(const TableInfo& table_info, std::unique_ptr<LogicalPlan>&& child = nullptr)
      : table_info(table_info),
        child(std::move(child)) {}

  void accept_visitor(LogicalPlanVisitor& visitor) override {
    visitor.visit(*this);
  }

  std::unique_ptr<LogicalPlan> clone() const override {
    std::unique_ptr<LogicalPlan> child_clone = child ? child->clone() : nullptr;
    return std::make_unique<DeletionPlan>(table_info, std::move(child_clone));
  }

  bool is_action() const override {
    return true;
  }

  std::ostream& print_to_ostream(std::ostream& os, int indent = 0) const override {
    os << std::string(indent, ' ') << "Delete(" << table_info.name << ")";
    if (child != nullptr) {
      os << "\n";
      child->print_to_ostream(os, indent + 2);
    }
    return os;
  }
};
