// test_join_order_beam.cc
// 5 unit tests for beam_search_join_order.
//
// Each test builds RelationPlan children directly (no parser) with known
// cardinalities, calls beam_search_join_order, and checks that the first
// element of the result is the expected cheapest probe table.
//
// Tests:
//   1. Two tables — large declared first, small second → must reorder
//   2. Three-table chain, declared big→medium→small → small must start
//   3. Two tables — small already declared first → must stay
//   4. Four-table chain (1000,500,100,10) declared a→b→c→d → d must start
//   5. Star schema: hub(5000), leaf1(200), leaf2(50) → leaf2 must start

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "query/optimizer/join_order.h"
#include "query/parser/logical_plan/plans.h"
#include "relational_model/schema.h"
#include "relational_model/table_info.h"
#include "system/system.h"
#include "system/transaction_manager.h"

// ---------------------------------------------------------------------------
// helpers
// ---------------------------------------------------------------------------

// Build a Column whose alias and table both equal `alias`, with column `col`.
static Column make_col(const std::string& alias, const std::string& col) {
    return Column(alias, alias, ColumnInfo{col, DataType::INT, 0});
}

// Set the cardinality of a table that has already been created.
static void set_card(const std::string& table, uint64_t card, TxID tx) {
    auto* ti = const_cast<TableInfo*>(catalog.get_table_info(table, tx));
    if (ti) ti->cardinality = card;
}

// Build RelationPlan children (alias == table name) and run beam search.
static std::vector<size_t> run(
    const std::vector<std::string>& aliases,
    const std::vector<std::pair<Column, Column>>& join_cols,
    TxID tx)
{
    std::vector<std::unique_ptr<LogicalPlan>> children;
    for (const auto& a : aliases)
        children.push_back(std::make_unique<RelationPlan>(a, a));
    return beam_search_join_order(children, join_cols, tx);
}

// ---------------------------------------------------------------------------
// main
// ---------------------------------------------------------------------------

int main() {
    std::filesystem::remove_all("Data/test_join_order_beam");
    System system("Data/test_join_order_beam");

    // --- Create all tables used by the 5 tests in one setup transaction ---
    Schema s2({{"id", DataType::INT}, {"fk", DataType::INT}});

    TxID stx = transaction_mgr.start_transaction(IsolationLevel::READ_COMMITTED);

    catalog.create_table("one_large",   s2, stx);  // test 1
    catalog.create_table("one_small",   s2, stx);
    catalog.create_table("two_big",     s2, stx);  // test 2
    catalog.create_table("two_medium",  s2, stx);
    catalog.create_table("two_small",   s2, stx);
    catalog.create_table("three_a",     s2, stx);  // test 3
    catalog.create_table("three_b",     s2, stx);
    catalog.create_table("four_a",      s2, stx);  // test 4
    catalog.create_table("four_b",      s2, stx);
    catalog.create_table("four_c",      s2, stx);
    catalog.create_table("four_d",      s2, stx);
    catalog.create_table("five_hub",    s2, stx);  // test 5
    catalog.create_table("five_leaf_a", s2, stx);
    catalog.create_table("five_leaf_b", s2, stx);    catalog.create_table("six_a",        s2, stx);  // test 6
    catalog.create_table("six_b",        s2, stx);
    catalog.create_table("six_c",        s2, stx);
    set_card("one_large",   1000, stx);
    set_card("one_small",     10, stx);
    set_card("two_big",    10000, stx);
    set_card("two_medium",   100, stx);
    set_card("two_small",     10, stx);
    set_card("three_a",       10, stx);
    set_card("three_b",     1000, stx);
    set_card("four_a",      1000, stx);
    set_card("four_b",       500, stx);
    set_card("four_c",       100, stx);
    set_card("four_d",        10, stx);
    set_card("five_hub",    5000, stx);
    set_card("five_leaf_a",  200, stx);
    set_card("five_leaf_b",   50, stx);
    set_card("six_a",         50, stx);
    set_card("six_b",         30, stx);
    set_card("six_c",       8000, stx);

    transaction_mgr.commit_transaction(stx);

    // --- Run tests ---
    int passed = 0, failed = 0;
    TxID tx = transaction_mgr.start_transaction(IsolationLevel::READ_COMMITTED);

    // ------------------------------------------------------------------
    // Test 1: two tables, large(1000) declared first, small(10) second.
    // join: t1_large.id = t1_small.fk
    // Expected: result[0] == 1  (t1_small must be probed first)
    // ------------------------------------------------------------------
    {
        auto order = run(
            {"one_large", "one_small"},
            {{ make_col("one_large", "id"), make_col("one_small", "fk") }},
            tx
        );
        // full order must be [1, 0]: one_small then one_large
        bool ok = order == std::vector<size_t>{1, 0};
        if (ok) {
            std::cout << "[PASS] Test 1: two-table reorder — order is [one_small, one_large]\n";
            ++passed;
        } else {
            std::cout << "[FAIL] Test 1: expected [1,0] (one_small, one_large), got [";
            for (size_t i = 0; i < order.size(); ++i) std::cout << order[i] << (i+1<order.size()?",":"");
            std::cout << "]\n       (one_large=1000 rows, one_small=10 rows)\n";
            ++failed;
        }
    }

    // ------------------------------------------------------------------
    // Test 2: three-table chain, declared big(10000)→medium(100)→small(10).
    // joins: big.id = medium.fk,  medium.id = small.fk
    // Expected: result[0] == 2  (t2_small starts the chain)
    // ------------------------------------------------------------------
    {
        auto order = run(
            {"two_big", "two_medium", "two_small"},
            {
                { make_col("two_big",    "id"), make_col("two_medium", "fk") },
                { make_col("two_medium", "id"), make_col("two_small",  "fk") }
            },
            tx
        );
        // full order must be [2, 1, 0]: two_small → two_medium → two_big
        bool ok = order == std::vector<size_t>{2, 1, 0};
        if (ok) {
            std::cout << "[PASS] Test 2: three-table chain — order is [two_small, two_medium, two_big]\n";
            ++passed;
        } else {
            std::cout << "[FAIL] Test 2: expected [2,1,0] (two_small, two_medium, two_big), got [";
            for (size_t i = 0; i < order.size(); ++i) std::cout << order[i] << (i+1<order.size()?",":"");
            std::cout << "]\n       (chain two_big(10000)-two_medium(100)-two_small(10))\n";
            ++failed;
        }
    }

    // ------------------------------------------------------------------
    // Test 3: two tables, small(10) already declared first, large(1000) second.
    // join: t3_a.id = t3_b.fk
    // Expected: result[0] == 0  (already optimal, no reorder)
    // ------------------------------------------------------------------
    {
        auto order = run(
            {"three_a", "three_b"},
            {{ make_col("three_a", "id"), make_col("three_b", "fk") }},
            tx
        );
        // full order must be [0, 1]: three_a then three_b (already optimal)
        bool ok = order == std::vector<size_t>{0, 1};
        if (ok) {
            std::cout << "[PASS] Test 3: already-optimal order preserved — order is [three_a, three_b]\n";
            ++passed;
        } else {
            std::cout << "[FAIL] Test 3: expected [0,1] (three_a, three_b), got [";
            for (size_t i = 0; i < order.size(); ++i) std::cout << order[i] << (i+1<order.size()?",":"");
            std::cout << "]\n       (three_a=10, three_b=1000; correct order must not be reversed)\n";
            ++failed;
        }
    }

    // ------------------------------------------------------------------
    // Test 4: four-table chain, declared a(1000)→b(500)→c(100)→d(10).
    // joins: a.id=b.fk, b.id=c.fk, c.id=d.fk
    // Expected: result[0] == 3  (t4_d, the smallest, starts the chain)
    // ------------------------------------------------------------------
    {
        auto order = run(
            {"four_a", "four_b", "four_c", "four_d"},
            {
                { make_col("four_a", "id"), make_col("four_b", "fk") },
                { make_col("four_b", "id"), make_col("four_c", "fk") },
                { make_col("four_c", "id"), make_col("four_d", "fk") }
            },
            tx
        );
        // full order must be [3, 2, 1, 0]: four_d → four_c → four_b → four_a
        bool ok = order == std::vector<size_t>{3, 2, 1, 0};
        if (ok) {
            std::cout << "[PASS] Test 4: four-table chain — order is [four_d, four_c, four_b, four_a]\n";
            ++passed;
        } else {
            std::cout << "[FAIL] Test 4: expected [3,2,1,0] (four_d, four_c, four_b, four_a), got [";
            for (size_t i = 0; i < order.size(); ++i) std::cout << order[i] << (i+1<order.size()?",":"");
            std::cout << "]\n       (chain four_a(1000)-four_b(500)-four_c(100)-four_d(10))\n";
            ++failed;
        }
    }

    // ------------------------------------------------------------------
    // Test 5: star schema, declared hub(5000)→leaf1(200)→leaf2(50).
    // joins: hub.id=leaf1.fk,  hub.id=leaf2.fk  (leaf1 and leaf2 NOT connected)
    // Expected: result[0] == 2  (t5_leaf2, the smallest leaf, starts)
    //
    // Rationale: starting from leaf2(50), join hub via selectivity → still 50 rows,
    // then join leaf1 → still 50 rows.  Total cost ≈ 150.
    // Starting from leaf1(200) costs ≈ 450; starting from hub costs ≈ 5100.
    // ------------------------------------------------------------------
    {
        auto order = run(
            {"five_hub", "five_leaf_a", "five_leaf_b"},
            {
                { make_col("five_hub", "id"), make_col("five_leaf_a", "fk") },
                { make_col("five_hub", "id"), make_col("five_leaf_b", "fk") }
            },
            tx
        );
        // full order must be [2, 0, 1]: five_leaf_b → five_hub → five_leaf_a
        // leaf_b(50) first, then hub(5000) to connect via its predicate, then leaf_a(200)
        bool ok = order == std::vector<size_t>{2, 0, 1};
        if (ok) {
            std::cout << "[PASS] Test 5: star schema — order is [five_leaf_b, five_hub, five_leaf_a]\n";
            ++passed;
        } else {
            std::cout << "[FAIL] Test 5: expected [2,0,1] (five_leaf_b, five_hub, five_leaf_a), got [";
            for (size_t i = 0; i < order.size(); ++i) std::cout << order[i] << (i+1<order.size()?",":"");
            std::cout << "]\n       (star: five_hub(5000), five_leaf_a(200), five_leaf_b(50))\n";
            ++failed;
        }
    }

    transaction_mgr.commit_transaction(tx);

    // ------------------------------------------------------------------
    // Test 6: double-predicate advantage — medium table should start first.
    //
    // Tables (declared order A=0, B=1, C=2):
    //   six_a: 50 rows   (medium)
    //   six_b: 30 rows   (smallest)
    //   six_c: 8000 rows (huge)
    //
    // Predicates:
    //   A-B : 1 predicate   (six_a.col_x = six_b.col_x)
    //   A-C : 2 predicates  (six_a.col_y = six_c.col_y  AND  six_a.col_z = six_c.col_z)
    //   B-C : 1 predicate   (six_b.col_w = six_c.col_w)
    //
    // Why [A, C, B] = [0, 2, 1] is optimal:
    //   Starting from A(50), the two A-C predicates give selectivity (1/8000)^2,
    //   shrinking the A⋈C result to ~0.006 rows before B is even touched.
    //   Starting from B(30, the smallest) forces single-predicate joins throughout
    //   and costs more in total.
    //
    // Expected: [0, 2, 1]  — medium A first, huge C second, tiny B last.
    // ------------------------------------------------------------------
    TxID tx6 = transaction_mgr.start_transaction(IsolationLevel::READ_COMMITTED);
    {
        auto order = run(
            {"six_a", "six_b", "six_c"},
            {
                { make_col("six_a", "col_x"), make_col("six_b", "col_x") },  // A-B
                { make_col("six_a", "col_y"), make_col("six_c", "col_y") },  // A-C (1st pred)
                { make_col("six_a", "col_z"), make_col("six_c", "col_z") },  // A-C (2nd pred)
                { make_col("six_b", "col_w"), make_col("six_c", "col_w") },  // B-C
            },
            tx6
        );
        // full order must be [0, 2, 1]: six_a → six_c → six_b
        bool ok = order == std::vector<size_t>{0, 2, 1};
        if (ok) {
            std::cout << "[PASS] Test 6: double-predicate — order is [six_a, six_c, six_b]\n";
            ++passed;
        } else {
            std::cout << "[FAIL] Test 6: expected [0,2,1] (six_a, six_c, six_b), got [";
            for (size_t i = 0; i < order.size(); ++i) std::cout << order[i] << (i+1<order.size()?",":"");
            std::cout << "]\n";
            std::cout << "       six_a(50) has TWO predicates with six_c(8000), making six_a→six_c\n";
            std::cout << "       extremely cheap despite six_c's size. Starting from six_b(30,\n";
            std::cout << "       the smallest) misses this double-selectivity and costs more.\n";
            ++failed;
        }
    }
    transaction_mgr.commit_transaction(tx6);

    // --- Summary ---
    std::cout << "\n" << passed << "/" << (passed + failed) << " passed";
    if (failed > 0)
        std::cout << ", " << failed << " FAILED";
    std::cout << "\n";

    return failed > 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}
