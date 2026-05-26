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

  Schema schema_a({{"id", DataType::INT}, {"word", DataType::STR}});

  std::string table_a = "rehash_left";

  if (!catalog.table_exists(table_a, txid)) {
    catalog.create_table(table_a, schema_a, txid);

    for (int64_t i = 0; i < 3001; ++i) {
      std::string word = {
          static_cast<char>('a' + (i % 26)), static_cast<char>('a' + ((i + 1) % 26)),
          static_cast<char>('a' + ((i + 2) % 26))
      };

      catalog.insert_record(table_a, Record({i, Value(word)}), txid);
    }
  }

  Schema schema_b({{"id", DataType::INT}, {"a", DataType::INT}, {"tag", DataType::STR}});
  std::string table_b = "rehash_right";

  if (!catalog.table_exists(table_b, txid)) {
    catalog.create_table(table_b, schema_b, txid);

    Record r = {{0, 3000, Value("match")}};
    catalog.insert_record(table_b, r, txid);

    for (int i = 1; i < 10; ++i) {
      Record r = {{i, i, Value("match")}};
      catalog.insert_record(table_b, r, txid);
    }
  }

  std::string query = "SELECT * FROM rehash_left, rehash_right "
                      "WHERE rehash_left.id == rehash_right.a";

  std::filesystem::path output_dir = "data/outputs";
  std::filesystem::path ref_dir = "data/references";

  std::filesystem::create_directories(output_dir);

  auto out_path = output_dir / "hash_join_2.out";
  auto ref_path = ref_dir / "hash_join_2.ref";

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