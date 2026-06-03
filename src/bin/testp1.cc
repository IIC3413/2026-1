#include "common.h"

// This test simulates two transactions T1 and T2. First it's created T2 with SI isolation level,
// then T1 starts with RC isolation level and updates a row and commits.
// T2 should not see the update because its snapshot predates T1's commit, so it should read the old value.


void setup_tx(){
    auto setup = transaction_mgr.start_transaction(IsolationLevel::READ_COMMITTED);
    catalog.create_table(ISOLATION_TABLE, ISOLATION_SCHEMA, setup);
    for (int i = 0; i < 10; ++i) {
        insert_row(i, i * 10, setup);
    }
    transaction_mgr.commit_transaction(setup);
}

void transaction_1(){
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // wait for T2 to start and take snapshot
    auto tx1 = transaction_mgr.start_transaction(IsolationLevel::READ_COMMITTED);
    std::string query = "UPDATE t SET v = 161 WHERE id == 1";
    bool explain = false;
    auto logical_plan = Parser::parse(query, explain, tx1);
    std::cout << "T1 update: " << query << std::endl;
    process_query(std::move(logical_plan), explain, tx1, std::cout);
    transaction_mgr.commit_transaction(tx1);
}

void transaction_2(){
    auto tx2 = transaction_mgr.start_transaction(IsolationLevel::SNAPSHOT_ISOLATION);
    std::string query = "SELECT * FROM t";
    bool explain = false;
    std::this_thread::sleep_for(std::chrono::milliseconds(300)); // wait for T1 to commit
    auto logical_plan = Parser::parse(query, explain, tx2);
    std::cout << "T2 select: " << query << std::endl;
    process_query(std::move(logical_plan), explain, tx2, std::cout);
    transaction_mgr.commit_transaction(tx2);
    std::cout << "T2 should see old value" << std::endl;
}

int main() {
    std::filesystem::remove_all("Data/isolation_test_p1");
    auto system = System("Data/isolation_test_p1");

    setup_tx();

    std::thread t1(transaction_1);
    std::thread t2(transaction_2);

    t1.join();
    t2.join();

    return 0;
}