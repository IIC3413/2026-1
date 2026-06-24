// test_join_order_10 — beam search join ordering with 10 tables.
//
// Tables ta..tj form a chain: tx.id == ty.fk for consecutive pairs.
// Cardinalities are intentionally scrambled so the beam search has real work.
//
// Cardinality assignment (index = position in NAMES array):
//   ta=50000  tb=200  tc=10000  td=50    te=5000
//   tf=10     tg=1000 th=500    ti=100   tj=25000
//
// Ascending: tf(10) td(50) ti(100) tb(200) th(500)
//            tg(1000) te(5000) tc(10000) tj(25000) ta(50000)

#include <algorithm>
#include <climits>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "query/optimizer/join_order.h"
#include "query/optimizer/optimizer.h"
#include "query/parser/logical_plan/plans.h"
#include "query/parser/parser.h"
#include "relational_model/record.h"
#include "relational_model/schema.h"
#include "relational_model/value.h"
#include "system/system.h"
#include "system/transaction_manager.h"

static constexpr int N = 10;

static const char* NAMES[N] = {
    "ta", "tb", "tc", "td", "te", "tf", "tg", "th", "ti", "tj"
};

// Scrambled cardinalities indexed by position in NAMES
static const uint64_t CARDS[N] = {
    50000, 200, 10000, 50, 5000, 10, 1000, 500, 100, 25000
};

// Map alias string → index in NAMES
static int name_index(const std::string& alias) {
    for (int i = 0; i < N; i++)
        if (alias == NAMES[i]) return i;
    return -1;
}

int main() {
    std::filesystem::remove_all("Data/test_join_order_10");
    System system("Data/test_join_order_10");

    Schema s({{"id", DataType::INT}, {"fk", DataType::INT}});

    // Create all 10 tables and set their cardinalities
    TxID setup = transaction_mgr.start_transaction(IsolationLevel::READ_COMMITTED);
    for (int i = 0; i < N; i++) {
        catalog.create_table(NAMES[i], s, setup);
        auto* ti = const_cast<TableInfo*>(catalog.get_table_info(NAMES[i], setup));
        if (ti) ti->cardinality = CARDS[i];
    }
    transaction_mgr.commit_transaction(setup);

    // Build a chain join: ta JOIN tb ... JOIN tj
    // predicates: ta.id == tb.fk, tb.id == tc.fk, ..., ti.id == tj.fk
    std::string from = NAMES[0];
    for (int i = 1; i < N; i++) { from += ", "; from += NAMES[i]; }

    std::string where;
    for (int i = 0; i < N - 1; i++) {
        if (i > 0) where += " AND ";
        where += std::string(NAMES[i]) + ".id == " + NAMES[i+1] + ".fk";
    }

    std::string query = std::string("SELECT ") + NAMES[0] + ".id FROM " + from + " WHERE " + where;
    std::cout << "=== Query ===\n" << query << "\n\n";

    uint64_t tx_id = 0;
    auto plan = Parser::parse(query, false, tx_id);

    // Walk to the JoinPlan
    auto* proj = dynamic_cast<ProjectionPlan*>(plan.get());
    LogicalPlan* inner = proj ? proj->child.get() : plan.get();
    auto* join_plan = dynamic_cast<JoinPlan*>(inner);

    if (!join_plan) {
        std::cout << "No JoinPlan at root.\n";
        return 1;
    }

    auto get_alias = [](const std::unique_ptr<LogicalPlan>& child) -> std::string {
        if (auto* rel = dynamic_cast<RelationPlan*>(child.get())) return rel->alias;
        if (auto* sel = dynamic_cast<SelectionPlan*>(child.get()))
            if (auto* rel = dynamic_cast<RelationPlan*>(sel->child.get())) return rel->alias;
        return "?";
    };

    // Print parser order with cardinalities
    std::cout << "=== Parser order ===\n";
    for (const auto& child : join_plan->children) {
        std::string alias = get_alias(child);
        int idx = name_index(alias);
        std::cout << "  " << alias << "  card=" << (idx >= 0 ? CARDS[idx] : 0) << "\n";
    }

    // Run beam search
    TxID est_tx = transaction_mgr.start_transaction(IsolationLevel::READ_COMMITTED);
    auto order = beam_search_join_order(join_plan->children, join_plan->join_columns, est_tx);
    transaction_mgr.commit_transaction(est_tx);

    // Print beam order with cardinalities
    std::cout << "\n=== Beam-search order ===\n";
    for (size_t pos = 0; pos < order.size(); pos++) {
        std::string alias = get_alias(join_plan->children[order[pos]]);
        int idx = name_index(alias);
        std::cout << "  [" << pos << "] " << alias << "  card=" << (idx >= 0 ? CARDS[idx] : 0) << "\n";
    }

    // Verify: first table in the order is the globally smallest (always achievable)
    std::string first_alias = get_alias(join_plan->children[order[0]]);
    int first_idx = name_index(first_alias);
    uint64_t first_card = first_idx >= 0 ? CARDS[first_idx] : UINT64_MAX;

    uint64_t min_card = *std::min_element(CARDS, CARDS + N);
    bool ok = (first_card == min_card);

    std::cout << "\n=== Result: " << (ok ? "PASS" : "FAIL")
              << " — first table is " << first_alias << " (card=" << first_card << ")"
              << ", global minimum=" << min_card << " ===\n";
    std::cout << "Note: full order is not expected to be cardinality-sorted in a chain join.\n"
              << "      Predicates constrain reachability; beam search respects them.\n";

    return ok ? 0 : 1;
}
