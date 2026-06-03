#include "common.h"

#include <sstream>

// This test forces the call of the undo() method of heap file, by making
// a transaction that modifies a row and then aborts.
//

void setup_tx(){
    auto setup = transaction_mgr.start_transaction(IsolationLevel::READ_COMMITTED);
    catalog.create_table(ISOLATION_TABLE, ISOLATION_SCHEMA, setup);
    for (int i = 0; i < 10; ++i) {
        insert_row(i, i * 10, setup);
    }
    transaction_mgr.commit_transaction(setup);
}

void transaction_1(){
    auto tx1 = transaction_mgr.start_transaction(IsolationLevel::READ_COMMITTED);
    std::string update_query = "UPDATE t SET v = 161 WHERE id == 1";
    bool explain = false;
    auto logical_plan = Parser::parse(update_query, explain, tx1);
    std::cout << "T1 update: " << update_query << std::endl;
    process_query(std::move(logical_plan), explain, tx1, std::cout);
    transaction_mgr.abort_transaction(tx1);
}

void transaction_2(){
    auto tx2 = transaction_mgr.start_transaction(IsolationLevel::READ_COMMITTED);
    std::ostringstream out;
    std::string select_query = "SELECT * FROM t";
    bool explain = false;
    auto logical_plan = Parser::parse(select_query, explain, tx2);
    std::cout << "T2 select: " << select_query << std::endl;
    process_query(std::move(logical_plan), explain, tx2, std::cout);
    transaction_mgr.commit_transaction(tx2);

}

int main() {
    // Notice that this runs only on one thread.
    std::filesystem::remove_all("Data/isolation_test_p2");
    auto system = System("Data/isolation_test_p2");

    setup_tx();

    transaction_1();
    transaction_2();

    return 0;
}