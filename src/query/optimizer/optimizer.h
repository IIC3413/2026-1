#pragma once

#include <map>
#include <memory>
#include <set>
#include <vector>

#include "query/executor/expr/expr.h"
#include "query/executor/query_action.h"
#include "query/executor/query_iter.h"
#include "query/parser/logical_plan/expr/expr_plan.h"
#include "query/parser/logical_plan/expr/expr_plan_visitor.h"
#include "query/parser/logical_plan/logical_plan.h"

using PhysicalPlan = std::variant<std::unique_ptr<QueryIter>, std::unique_ptr<QueryAction>>;

class ExprOptimizer : public ExprPlanVisitor {
public:
  std::vector<Column> columns;

  ExprOptimizer(std::vector<Column>&& columns)
      : columns(std::move(columns)) {}

  std::unique_ptr<Expr> current_expr;

  void visit(ExprPlanBetween&) override;

  void visit(ExprPlanLike&) override;

  void visit(ExprPlanColumn&) override;

  void visit(ExprPlanTerm&) override;

  void visit(ExprPlanEquals&) override;

  void visit(ExprPlanNotEquals&) override;

  void visit(ExprPlanLess&) override;

  void visit(ExprPlanLessOrEquals&) override;

  void visit(ExprPlanArithmetic&) override;
};

class Optimizer : public LogicalPlanVisitor {
public:
  Optimizer(TxID tx_id)
      : LogicalPlanVisitor(tx_id) {};

  std::unique_ptr<QueryIter> current_iter;

  std::unique_ptr<QueryAction> current_action;

  // the plans are navigated via DFS, remembering how many usages each column have
  std::map<Column, size_t> column_usage;

  std::map<Column, std::pair<Value, Value>> column_range;

  // alias to column
  std::map<std::string, Column> between_optimizations;

  std::set<ExprPlan*> deleted_expr_plans;

  PhysicalPlan create_physical_plan(std::unique_ptr<LogicalPlan>);

  void try_set_lower_bound(const Column& column, Value&& value);

  void try_set_upper_bound(const Column& column, Value&& value);

  void visit(CartesianProductPlan&) override;

  void visit(JoinPlan&) override;

  void visit(LeftOuterJoinPlan&) override;

  void visit(FullOuterJoinPlan&) override;

  void visit(ProjectionPlan&) override;

  void visit(RelationPlan&) override;

  void visit(SelectionPlan&) override;

  void visit(CreationPlan&) override;

  void visit(InsertionPlan&) override;

  void visit(IndexCreationPlan&) override;
};
