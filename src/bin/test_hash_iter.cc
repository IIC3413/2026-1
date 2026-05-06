#include <filesystem>
#include <fstream>
#include <iostream>

#include "query/executor/hash_join/hash_table.h"
#include "relational_model/schema.h"
#include "query/executor/hash_join/hash_table_iter.h"

/*
Output esperado:

0:(3,"papa")
1:(2,"papa")
2:(0,"papa")
3:(4,"choclo")
4:(3,"papa")
5:(2,"papa")
6:(0,"papa")
*/

void print_inter(HashTable& hash_table, std::vector<Value> keys, std::ostream& out) {
  int record_count = 0;
  for (auto& key: keys) {
    auto iter = hash_table.probe(key);
    iter->begin();
    auto record = iter->next();
    while (!record.invalid()) {
      out << record_count << ":(" << record.to_string() << ")\n";
      record = iter->next();
      ++record_count;
    }
  }
}

int main() {
  // Schema
  Schema schema({{"indice", DataType::INT}, {"vegetal", DataType::STR}});

  std::vector<DataType> datatypes;
  datatypes.reserve(schema.columns.size());
  for (const auto& column : schema.columns) {
    datatypes.push_back(column.datatype);
  }

  // Hash table on column "vegetal"
  HashTable hash_table (1, datatypes);

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

  auto keys = {Value("papa"), Value("choclo"), Value("esparrago"), Value("papa")};

  print_inter(hash_table, keys, std::cout);

  return 0;
}