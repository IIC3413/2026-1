#pragma once

// Shared helpers for all isolation-level tests.
// Include this directly in each test .cc file.

#include <atomic>
#include <chrono>
#include <filesystem>
#include <iostream>
#include <string>
#include <thread>

#include "exceptions/exceptions.h"
#include "relational_model/record.h"
#include "relational_model/schema.h"
#include "relational_model/value.h"
#include "storage/heap_file/heap_file.h"
#include "storage/heap_file/heap_file_iter.h"
#include "storage/rid.h"
#include "system/catalog.h"
#include "system/system.h"
#include "query/optimizer/optimizer.h"
#include "query/parser/parser.h"
#include "system/system.h"



using namespace std::chrono_literals;

// Table schema: (id INT, v INT)
inline const Schema ISOLATION_SCHEMA({{"id", DataType::INT}, {"v", DataType::INT}});
inline const char* const ISOLATION_TABLE = "t";

// Scan heap file for the row with the given id visible to tx.
// Returns the v-value, or -1 if the row is not found / not visible.
inline int64_t read_v(HeapFile* hf, TxID tx, int64_t target_id) {
    auto iter = hf->get_record_iter(tx);
    iter->begin();
    for (;;) {
        auto rec = iter->next();
        if (rec.invalid()) return -1;
        // HeapFileIter appends the first_rid as values[2]; data is values[0..1]
        if (rec.values[0].as_int() == target_id)
            return rec.values[1].as_int();
    }
}

// Count rows visible to tx.
inline int count_visible(HeapFile* hf, TxID tx) {
    int n = 0;
    auto iter = hf->get_record_iter(tx);
    iter->begin();
    for (;;) {
        auto rec = iter->next();
        if (rec.invalid()) break;
        ++n;
    }
    return n;
}

// Insert a single (id, v) row and return the first RID.
inline RID insert_row(int64_t id, int64_t v, TxID tx) {
    return catalog.insert_record(ISOLATION_TABLE, Record({Value(id), Value(v)}), tx);
}

// Update a row (by first_rid) to new (id, v).
// Discards the returned new RID; callers can recover via read_v.
inline void update_row(RID first_rid, int64_t id, int64_t v, TxID tx) {
    catalog.update_record(ISOLATION_TABLE, first_rid, Record({Value(id), Value(v)}), tx);
}

// Delete a row by its first RID.
inline void delete_row(RID first_rid, TxID tx) {
    catalog.delete_record(ISOLATION_TABLE, first_rid, tx);
}

// Get the HeapFile for the test table (0 is fine for DDL-level access).
inline HeapFile* get_hf() {
    return catalog.get_table_info(ISOLATION_TABLE, 1)->heap_file.get();
}

inline void process_query(std::unique_ptr<LogicalPlan> logical_plan, bool explain, TxID tx_id, std::ostream& out) {
  Optimizer optimizer(tx_id);
  auto physical_plan = optimizer.create_physical_plan(std::move(logical_plan));

  if (std::holds_alternative<std::unique_ptr<QueryAction>>(physical_plan)) {
    auto action = std::move(std::get<std::unique_ptr<QueryAction>>(physical_plan));
    action->execute();
  } else if (std::holds_alternative<std::unique_ptr<QueryIter>>(physical_plan)) {
    auto query_iter = std::move(std::get<std::unique_ptr<QueryIter>>(physical_plan));

    if (explain) {
      std::cout << "\n=== Physical Plan ===\n";
      query_iter->print_to_ostream(std::cout, 0);
      std::cout << std::endl;
    }

    query_iter->begin();
    Record record = query_iter->next();

    int record_count = 0;
    while (!record.invalid()) {
      out << record_count << ":(" << record.to_string() << ")\n";
      record = query_iter->next();
      ++record_count;
    }
  }
}

// -------------------------------------------------------------------------
// Test reporter
// -------------------------------------------------------------------------
struct TestReport {
    bool all_pass = true;

    void check(bool cond, const std::string& msg) {
        if (cond) {
            std::cout << "  [PASS] " << msg << "\n";
        } else {
            std::cout << "  [FAIL] " << msg << "\n";
            all_pass = false;
        }
    }

    // For assertions that are EXPECTED TO FAIL due to a known unfixed bug.
    // The test will print [KNOWN BUG - FAIL] instead of [FAIL] so the suite
    // still clearly fails, but the cause is documented. Once the bug is fixed
    // this will print [PASS].
    void check_bug(bool correct_condition, const std::string& msg) {
        if (correct_condition) {
            std::cout << "  [PASS] (bug fixed!) " << msg << "\n";
        } else {
            std::cout << "  [KNOWN BUG - FAIL] " << msg << "\n";
            all_pass = false;
        }
    }

    int result() const {
        std::cout << "\n" << (all_pass ? "=== TEST PASSED ===" : "=== TEST FAILED ===") << "\n";
        return all_pass ? 0 : 1;
    }
};

// Convenience: fresh-database setup for a test.
// Removes any leftover data directory, creates the System and the table,
// runs the setup lambda, then returns the HeapFile pointer.
//
// Usage:
//   auto [sys, hf] = setup_test("Data/isolation_rc1", [](HeapFile* hf) {
//       auto tx = transaction_mgr.start_transaction(IsolationLevel::READ_COMMITTED);
//       RID rid1 = insert_row(1, 10, tx);
//       transaction_mgr.commit_transaction(tx);
//   });
//
// Not used as a function here — each test just calls the setup inline for clarity.
