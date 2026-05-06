#pragma once

#include <memory>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include "query/parser/logical_plan/logical_plan.h"
#include "query/parser/logical_plan/logical_plan_visitor.h"

class IndexCreationPlan : public LogicalPlan {
public:
  std::string table_name;
  std::string column_name;

    IndexCreationPlan(const std::string& table_name, const std::string& column_name)
      : table_name(table_name),
        column_name(column_name) {}

  void accept_visitor(LogicalPlanVisitor& visitor) override {
    visitor.visit(*this);
  }

  std::unique_ptr<LogicalPlan> clone() const override {
    return std::make_unique<IndexCreationPlan>(table_name, column_name); // FIXME: está bien?
  }

  bool is_action() const override {
    return true;
  }

  std::ostream& print_to_ostream(std::ostream& os, int indent = 0) const override {
    os << std::string(indent, ' ');
    os << "IndexCreation(";
    os << table_name;
    os << ", " << column_name;
    return os << ")\n";
  }
};
