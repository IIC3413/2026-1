#include <filesystem>
#include <fstream>
#include <iostream>

#include "helper.h"
#include "query/executor/hash_join/hash_table.h"
#include "relational_model/schema.h"

int main() {
  // Schema
  Schema schema({{"indice", DataType::INT}, {"vegetal", DataType::STR}});

  std::vector<DataType> datatypes;
  datatypes.reserve(schema.columns.size());
  for (const auto& column : schema.columns) {
    datatypes.push_back(column.datatype);
  }

  // Hash table on column "vegetal"
  HashTable hash_table(1, datatypes);

  // Test data
  std::vector<Record> records = {
      {{0, Value("papa")}},
      {{1, Value("zanahoria")}},
      {{2, Value("papa")}},
      {{3, Value("papa")}},
      {{4, Value("choclo")}}
  };

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

  auto out_path = output_dir / "insert_1.out";
  auto ref_path = ref_dir / "insert_1.ref";

  if (!std::filesystem::exists(ref_path)) {
    std::cerr << "Error: reference output does not exist. \n";
    return EXIT_FAILURE;
  }

  std::ofstream out(out_path);

  if (!out) {
    std::cerr << "Error opening output file\n";
    return EXIT_FAILURE;
  }

  hash_table.print_hash_table(out);

  if (files_are_equal(out_path, ref_path)) {
    std::cout << "0.5\n";
  } else {
    std::cout << "0\n";
  }

  return EXIT_SUCCESS;
}
