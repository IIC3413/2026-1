#include <filesystem>
#include <fstream>
#include <iostream>

#include "helper.h"
#include "query/executor/hash_join/hash_table.h"
#include "relational_model/schema.h"

int main() {
  // Schema
  Schema schema({{"A", DataType::INT}, {"B", DataType::STR}});

  std::vector<DataType> datatypes;
  datatypes.reserve(schema.columns.size());
  for (const auto& column : schema.columns) {
    datatypes.push_back(column.datatype);
  }

  // Hash table on column "A"
  HashTable hash_table(0, datatypes);

  // Test data
  std::vector<Record> records;

  for (int64_t i = 0; i < 3500; ++i) {
    std::string word = {
        static_cast<char>('a' + (i % 26)), static_cast<char>('a' + ((i + 1) % 26)),
        static_cast<char>('a' + ((i + 2) % 26))
    };

    int64_t first_value = (i >= 2999) ? 2999 : i;

    records.push_back({{first_value, Value(word)}});
  }

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

  auto out_path = output_dir / "insert_3.out";
  auto ref_path = ref_dir / "insert_3.ref";

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