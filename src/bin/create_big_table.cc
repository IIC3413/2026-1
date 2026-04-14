#include "storage/heap_file/heap_file.h"
#include "system/system.h"
#include <iostream>
#include <memory>
#include <random>

/*
This test creates the table used for the tests of lab1.
This test creates the 0_to_test_table.tbl file, which is used to compare against the reference file
"0_valid_table.tbl".
*/

void fill_table2(HeapFile& heap_file) {
  // Schema1 = {A: int, B: str, C: str}
  for (int i = 0; i < 10; i++) {
    Value valA(i);
    Value valB("value: " + std::to_string(i));
    Value valC("value 2: " + std::to_string(i + 1));

    std::vector<Value> values = {valA, valB, valC};

    Record record(values);

    heap_file.insert_record(record, 0);
  }
}

int main() {
  auto system = System("data/example_db");

  Schema schema({{"A", DataType::INT}, {"B", DataType::INT}, {"C", DataType::STR}});

  Schema schema2({{"A", DataType::INT}, {"B", DataType::STR}, {"C", DataType::STR}});

  std::string table_name2 = "second_to_test_table";

  catalog.create_table("to_test_table", schema);
  auto table_info2 = catalog.create_table(table_name2, schema2);

  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<> length_distribution(4, 15);

  RID last_rid;
  int group_counter = 0;

  for (int i = 0; i <= 150; ++i) {
    if (i % 10 == 0) {
      group_counter++;
    }
    Value valA(group_counter);
    Value valB(i % 10);
    Value valC("{group: " + std::to_string(group_counter) + "value: " + std::to_string(i % 10) + "}");

    std::vector<Value> values = {valA, valB, valC};
    Record record(values);
    last_rid = catalog.insert_record("to_test_table", record, 0);
  }

  fill_table2(*table_info2->heap_file.get());

  return 0;
}