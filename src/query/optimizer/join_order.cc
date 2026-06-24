#include "join_order.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <unordered_map>

#include "query/parser/logical_plan/expr/expr_plans.h"
#include "query/parser/logical_plan/plans.h"
#include "system/system.h"

static double selectivity_of_expr(const ExprPlan& expr, double base_cardinality) {
  if (dynamic_cast<const ExprPlanEquals*>(&expr))
    return 1.0 / std::sqrt(std::max(base_cardinality, 2.0));
  if (dynamic_cast<const ExprPlanNotEquals*>(&expr))
    return 1.0 - 1.0 / std::sqrt(std::max(base_cardinality, 2.0));
  if (dynamic_cast<const ExprPlanLess*>(&expr) || dynamic_cast<const ExprPlanLessOrEquals*>(&expr))
    return 1.0 / 3.0;
  if (dynamic_cast<const ExprPlanBetween*>(&expr))
    return 1.0 / 4.0;
  if (dynamic_cast<const ExprPlanLike*>(&expr))
    return 0.1;
  return 1.0; // unknown predicate — no reduction
}

static double estimate_cardinality(const LogicalPlan& plan, TxID tx_id) {
  if (auto* rel = dynamic_cast<const RelationPlan*>(&plan)) {
    auto* ti = catalog.get_table_info(rel->table, tx_id);
    return ti ? std::max(1.0, static_cast<double>(ti->cardinality)) : 1e9;
  }
  if (auto* sel = dynamic_cast<const SelectionPlan*>(&plan)) {
    double cardinality = estimate_cardinality(*sel->child, tx_id);
    for (const auto& e : sel->expressions)
      cardinality *= selectivity_of_expr(*e, cardinality);
    return std::max(1.0, cardinality);
  }
  // other operator, we use a large sentinel so it sorts toward the end.
  return 1e9;
}

std::vector<size_t> beam_search_join_order(
    const std::vector<std::unique_ptr<LogicalPlan>>& children,
    const std::vector<std::pair<Column, Column>>& join_columns,
    TxID tx_id
) {
  const size_t n = children.size();
  assert(n <= 64); // bitmask fits in uint64_t

  // SQLite formula: K = min(64, max(5, N/2))
  const size_t beam_width = std::min(size_t(64), std::max(size_t(5), n / 2));

  // Gather per-child cardinality estimates and build alias -> index map
  // (only RelationPlan children contribute an alias for predicate matching).
  // Lab5: You can assume that only RelationPlan children are used.
  std::unordered_map<std::string, size_t> alias_to_idx;
  std::vector<double> cards(n);
  for (size_t i = 0; i < n; i++) {
    cards[i] = estimate_cardinality(*children[i], tx_id);
    if (auto* rel = dynamic_cast<const RelationPlan*>(children[i].get())) {
      alias_to_idx[rel->alias] = i;
    }
  }

  struct Path {
    uint64_t mask;
    double cost;
    double rows; // estimated output rows accumulated so far
    std::vector<size_t> order;
  };

  std::vector<Path> beam = {{0, 0.0, 1.0, {}}};

  //TODO: LAB5 Problem 2

  return beam.front().order;
}
