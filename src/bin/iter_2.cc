#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "helper.h"
#include "query/executor/hash_join/hash_table.h"
#include "query/executor/hash_join/hash_table_iter.h"
#include "relational_model/schema.h"

int main() {
  // Schema
  Schema schema({{"num", DataType::INT}, {"word", DataType::STR}});

  std::vector<DataType> datatypes;
  datatypes.reserve(schema.columns.size());
  for (const auto& column : schema.columns) {
    datatypes.push_back(column.datatype);
  }

  // Hash table on column "num"
  HashTable hash_table(0, datatypes);

  // Test data
  std::vector<Record> records = {{{2993, Value("match_1")}}, {{2993, Value("match_2")}}};


  for (const auto& record : records) {
    if (!hash_table.try_insert_record(record)) {
      std::cerr << "Failed to insert record: " << record.to_string() << "\n";
      return EXIT_FAILURE;
    }
  }

  // Writing results into outputs folder
  std::filesystem::path output_dir = "data/outputs";
  std::filesystem::path ref_dir = "data/references";

  std::filesystem::create_directories(output_dir);

  auto out_path = output_dir / "iter_2.out";
  auto ref_path = ref_dir / "iter_2.ref";

  if (!std::filesystem::exists(ref_path)) {
    std::cerr << "Error: reference output does not exist. \n";
    return EXIT_FAILURE;
  }
  
  std::ofstream out(out_path);

  if (!out) {
    std::cerr << "Error opening output file\n";
    return EXIT_FAILURE;
  }

  auto keys = {Value(4096), Value(2993)};
  print_inter(hash_table, keys, out);

  if (files_are_equal(out_path, ref_path)) {
    std::cout << "0.5\n";
  } else {
    std::cout << "0\n";
  }

  return EXIT_SUCCESS;
}