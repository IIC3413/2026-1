#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "query/parser/logical_plan/logical_plan.h"
#include "system/tx_id.h"

// Returns the optimal child ordering (indices into `children`) using
// SQLite-style beam search (K = min(64, max(5, N/2))).
//
// Children whose cardinality can be estimated (RelationPlan, SelectionPlan over
// RelationPlan) are costed via estimate_cardinality.  All others are tolerated:
// they still get a cost based on estimate_cardinality's 1e9 sentinel, so they
// are pushed toward the end of the join order rather than being mistaken for
// single-row tables.
std::vector<size_t> beam_search_join_order(
    const std::vector<std::unique_ptr<LogicalPlan>>& children,
    const std::vector<std::pair<Column, Column>>& join_columns,
    TxID tx_id);
