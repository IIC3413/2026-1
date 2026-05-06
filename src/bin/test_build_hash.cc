#include <filesystem>
#include <fstream>
#include <iostream>

#include "query/executor/hash_join/hash_table.h"
#include "relational_model/schema.h"

/*
Output esperado:

1652|zanahoria
0:(1,"zanahoria")

2763|papa
0:(3,"papa")
1:(2,"papa")
2:(0,"papa")

3728|choclo
0:(4,"choclo")*/

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
      return 1;
    }
  }

  hash_table.print_hash_table(std::cout);

  return 0;
}