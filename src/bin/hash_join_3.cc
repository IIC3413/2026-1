#include <filesystem>
#include <iostream>

#include "helper.h"
#include "query/optimizer/optimizer.h"
#include "query/parser/parser.h"
#include "storage/linear_hash_index/hash_index.h"
#include "system/system.h"

int main() {
  std::filesystem::remove_all("data/example_db");

  auto system = System("data/example_db");

  Transaction tx = transaction_mgr.start_transaction(IsolationLevel::READ_COMMITTED);
  auto txid = tx.get_id();

  Schema schema_a({{"id", DataType::INT}, {"key", DataType::INT}});

  std::string table_a = "large_left";

  if (!catalog.table_exists(table_a, txid)) {
    catalog.create_table(table_a, schema_a, txid);

    for (int i = 0; i < 20000; ++i) {
      std::vector<Value> values = {i, i % 3000};
      catalog.insert_record(table_a, Record(values), txid);
    }
  }

  Schema schema_b({{"id", DataType::INT}, {"key", DataType::INT}, {"tag", DataType::STR}});
  std::string table_b = "large_right";

  if (!catalog.table_exists(table_b, txid)) {
    catalog.create_table(table_b, schema_b, txid);

    for (int i = 0; i < 15; ++i) {
      std::vector<Value> b_values = {i, i * 200, Value("match")};
      catalog.insert_record(table_b, Record(b_values), txid);
    }
  }

  std::string query = "SELECT * FROM large_left, large_right "
                      "WHERE large_left.key == large_right.key";

  std::filesystem::path output_dir = "data/outputs";
  std::filesystem::path ref_dir = "data/references";

  std::filesystem::create_directories(output_dir);

  auto out_path = output_dir / "hash_join_3.out";
  auto ref_path = ref_dir / "hash_join_3.ref";

  if (!std::filesystem::exists(ref_path)) {
    std::cerr << "Error: reference output does not exist. \n";
    return EXIT_FAILURE;
  }

  std::ofstream out(out_path);

  bool explain = false;
  auto logical_plan = Parser::parse(query, explain, txid);
  process_query(std::move(logical_plan), explain, txid, out);

  transaction_mgr.commit_transaction(txid);

  if (files_are_equal(out_path, ref_path)) {
    std::cout << "1\n";
  } else {
    std::cout << "0\n";
  }

  return EXIT_SUCCESS;
}