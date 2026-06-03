#include "common.h"

#include <sstream>


// This test simulates three transactions T1, T2, and T3. First it's created T1 with RC isolation level, then T1 makes an update
// and commits. T2 starts with SI isolation level after T1's commit, so its snapshot is taken after T1's commit.
// Then T2 updates the same row and commits, T3 only verifies that T2's update is visible,
// which means that T2's snapshot was taken after T1's commit.


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
    transaction_mgr.commit_transaction(tx1);
}

void transaction_2(){
    auto tx2 = transaction_mgr.start_transaction(IsolationLevel::SNAPSHOT_ISOLATION);
    bool explain = false;
    std::string update_query = "UPDATE t SET v = 162 WHERE id == 1";
    auto logical_plan_update = Parser::parse(update_query, explain, tx2);
    std::cout << "T2 update: " << update_query << std::endl;
    process_query(std::move(logical_plan_update), explain, tx2, std::cout);
    transaction_mgr.commit_transaction(tx2);
}

void transaction_3(){
    auto tx3 = transaction_mgr.start_transaction(IsolationLevel::READ_COMMITTED);
    std::ostringstream out;
    std::string select_query = "SELECT * FROM t";
    bool explain = false;
    auto logical_plan = Parser::parse(select_query, explain, tx3);
    std::cout << "T3 select: " << select_query << std::endl;
    process_query(std::move(logical_plan), explain, tx3, std::cout);
    transaction_mgr.commit_transaction(tx3);

}

int main() {
    std::filesystem::remove_all("Data/isolation_test_p4");
    auto system = System("Data/isolation_test_p4");

    setup_tx();

    transaction_1();
    transaction_2();
    transaction_3();

    return 0;
}