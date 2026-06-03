
#include "common.h"

#include <sstream>

// This test simulates three transactions T1, T2 and T3. T1 starts with RC isolation level and deletes a row and commits.
// Before T1 commits, T2 starts with SI isolation level and takes a snapshot. After T1 commits, T3 starts with RC isolation level
// and tries to read the row. T2 should see the row because its snapshot predates T1's commit, so it should read the old value.
// T3 should not see the row because it starts after T1's commit.

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
    std::string delete_query = "DELETE FROM t WHERE id == 1";
    bool explain = false;
    auto logical_plan = Parser::parse(delete_query, explain, tx1);
    std::cout << "T1 delete: " << delete_query << std::endl;
    process_query(std::move(logical_plan), explain, tx1, std::cout);
    std::this_thread::sleep_for(std::chrono::milliseconds(200)); // wait for T2 to start and take snapshot
    transaction_mgr.commit_transaction(tx1);
}

void transaction_2(){
    auto tx2 = transaction_mgr.start_transaction(IsolationLevel::SNAPSHOT_ISOLATION);
    std::ostringstream out;
    std::string select_query = "SELECT * FROM t";
    bool explain = false;
    auto logical_plan = Parser::parse(select_query, explain, tx2);
    std::cout << "T2 select: " << select_query << std::endl;
    process_query(std::move(logical_plan), explain, tx2, std::cout);
    transaction_mgr.commit_transaction(tx2);
}

void transaction_3(){
    std::this_thread::sleep_for(std::chrono::milliseconds(400)); // wait for T1 to commit
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
    std::filesystem::remove_all("Data/isolation_test_p3");
    auto system = System("Data/isolation_test_p3");

    setup_tx();

    std::thread t1(transaction_1);
    std::thread t2(transaction_2);
    std::thread t3(transaction_3);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}