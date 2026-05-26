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

  Schema schema_a({{"id", DataType::INT}, {"key", DataType::STR}});

  std::string table_a = "skew_left";

  if (!catalog.table_exists(table_a, txid)) {
    catalog.create_table(table_a, schema_a, txid);
    std::cout << "Created table " << table_a << std::endl;

    for (int i = 0; i < 1000; ++i) {
      std::string key(1, static_cast<char>('a' + ((i * 3) % 26)));

      catalog.insert_record(table_a, Record({i, Value(key)}), txid);
    }
  }

  Schema schema_b({{"id", DataType::INT}, {"key", DataType::STR}, {"tag", DataType::STR}});
  std::string table_b = "skew_right";

  if (!catalog.table_exists(table_b, txid)) {
    catalog.create_table(table_b, schema_b, txid);
    std::cout << "\nCreated table " << table_b << std::endl;

    // una fila por key (suficiente para join)
    for (int i = 0; i < 26; ++i) {
      std::string key(1, static_cast<char>('a' + (i % 26)));
      std::vector<Value> b_values = {i, Value(key), Value("match")};
      catalog.insert_record(table_b, Record(b_values), txid);
    }
  }

  std::string query = "SELECT * FROM skew_left, skew_right WHERE skew_left.key == skew_right.key";

  std::filesystem::path output_dir = "data/outputs";
  std::filesystem::path ref_dir = "data/references";

  std::filesystem::create_directories(output_dir);

  auto out_path = output_dir / "hash_join_1.out";
  auto ref_path = ref_dir / "hash_join_1.ref";

  if (!std::filesystem::exists(ref_path)) {
    std::cerr << "Error: reference output does not exist. \n";
    return EXIT_FAILURE;
  }

  std::ofstream out(out_path);

  try {
    auto logical_plan = Parser::parse(query, false, txid);
    process_query(std::move(logical_plan), false, txid, out);
  } catch (const std::exception& e) {
    std::cerr << "Query exception: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  transaction_mgr.commit_transaction(txid);

  if (files_are_equal(out_path, ref_path)) {
    std::cout << "1\n";
  } else {
    std::cout << "0\n";
  }

  return EXIT_SUCCESS;
}
