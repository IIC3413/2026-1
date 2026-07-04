// test_like — exercises the custom LIKE matcher (expr_like.h).
//
// Creates a table with one STR column, inserts a set of known strings, then
// runs LIKE queries and checks the result counts.

#include <filesystem>
#include <iostream>
#include <string>

#include "query/optimizer/optimizer.h"
#include "query/parser/parser.h"
#include "relational_model/record.h"
#include "relational_model/schema.h"
#include "relational_model/value.h"
#include "system/system.h"
#include "system/transaction_manager.h"

static int passed = 0;
static int failed = 0;

// Run a SELECT COUNT query by iterating over results manually.
static int64_t count_results(const std::string& sql, TxID tx_id) {
    uint64_t tx_copy = tx_id;
    auto plan = Parser::parse(sql, false, tx_copy);
    Optimizer opt(tx_id);
    auto physical = opt.create_physical_plan(std::move(plan));
    auto& iter = std::get<std::unique_ptr<QueryIter>>(physical);
    iter->begin();
    int64_t n = 0;
    while (!iter->next().invalid()) n++;
    return n;
}

static void check(const std::string& label, const std::string& sql,
                  TxID tx_id, int64_t expected)
{
    int64_t got = count_results(sql, tx_id);
    bool ok = (got == expected);
    std::cout << (ok ? "[PASS]" : "[FAIL]") << " " << label
              << " — expected=" << expected << " got=" << got << "\n";
    if (ok) passed++; else failed++;
}

int main() {
    std::filesystem::remove_all("Data/test_like");
    System system("Data/test_like");

    Schema s({{"name", DataType::STR}});

    TxID setup = transaction_mgr.start_transaction(IsolationLevel::READ_COMMITTED);
    catalog.create_table("words", s, setup);
    transaction_mgr.commit_transaction(setup);

    // Insert test strings
    const char* rows[] = {
        "hello", "hell", "help", "world", "foo", "foobar", "foobaz",
        "100%done", "50%", "under_score", "_start", "back\\slash",
        "abc", "aXc", "a_c",
        nullptr
    };

    TxID ins = transaction_mgr.start_transaction(IsolationLevel::READ_COMMITTED);
    for (int i = 0; rows[i]; i++)
        catalog.insert_record("words", Record({Value(std::string(rows[i]))}), ins);
    transaction_mgr.commit_transaction(ins);

    TxID tx = transaction_mgr.start_transaction(IsolationLevel::READ_COMMITTED);

    // Basic % wildcard
    check("prefix foo%",   "SELECT words.name FROM words WHERE words.name LIKE \"foo%\"",   tx, 3); // foo, foobar, foobaz
    check("suffix %ld",    "SELECT words.name FROM words WHERE words.name LIKE \"%ld\"",    tx, 1); // world
    check("contains %oo%", "SELECT words.name FROM words WHERE words.name LIKE \"%oo%\"",   tx, 3); // foo, foobar, foobaz
    check("exact hello",   "SELECT words.name FROM words WHERE words.name LIKE \"hello\"",  tx, 1);
    check("empty pattern", "SELECT words.name FROM words WHERE words.name LIKE \"\"",       tx, 0);
    check("all %",         "SELECT words.name FROM words WHERE words.name LIKE \"%\"",      tx, 15);

    // _ wildcard (any single char)
    check("_ wildcard a_c","SELECT words.name FROM words WHERE words.name LIKE \"a_c\"",   tx, 3); // abc, aXc, a_c
    // hell_ = h,e,l,l,_ → exactly 5 chars → "hello" only ("help" is 4 chars)
    check("hell_",         "SELECT words.name FROM words WHERE words.name LIKE \"hell_\"",  tx, 1);

    // Escaped \% — literal percent sign
    check("literal \\%",   "SELECT words.name FROM words WHERE words.name LIKE \"%\\%%\"", tx, 2); // 100%done, 50%
    check("exact 50\\%",   "SELECT words.name FROM words WHERE words.name LIKE \"50\\%\"", tx, 1); // 50%

    // Escaped \_ — literal underscore
    check("literal \\_",   "SELECT words.name FROM words WHERE words.name LIKE \"%\\_%\"", tx, 3); // under_score, _start, a_c
    check("prefix \\_",    "SELECT words.name FROM words WHERE words.name LIKE \"\\_%\"",  tx, 1); // _start

    transaction_mgr.commit_transaction(tx);

    std::cout << "\n" << passed << " passed, " << failed << " failed.\n";
    return failed ? 1 : 0;
}
