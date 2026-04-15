#include <iostream>
#include <memory>

#include "relational_model/record.h"
#include "relational_model/schema.h"
#include "relational_model/value.h"
#include "storage/heap_file/heap_file.h"
#include "system/catalog.h"
#include "system/system.h"

/*
The created tables should be:
Table R:
A, B, C
0, 1,"value: 1"
1, 1,"value: 2"
2, 1,"value: 3"
3, 1,"value: 4"
4, 1,"value: 5"

Table S:
A, B, C,
"a10",1,0
"a11",1,2
"a12",1,4
"a13",1,6
"a14",1,8
"a15",1,10
"a16",1,12
"a17",1,14
"a18",1,16
"a19",1,18
    .
    .
    .

Table T:
A, B, C,
0,"9",2
1,"9",3
2,"9",4
3,"9",5
4,"9",6
5,"9",7
6,"9",8
7,"9",9
8,"9",10
*/

void print_records(const HeapFile& heap_file) {
  auto total_pages = file_mgr.count_pages(heap_file.file_id);
  //  std::cout << "Total pages: " << total_pages << std::endl;
  for (auto i = 0; i < total_pages; i++) {
    auto page = std::make_unique<HeapFilePage>(heap_file, i);
    for (int dir_slot = 0; dir_slot < page->get_dir_count(); dir_slot++) {
      auto record = page->get_record(dir_slot);
      //      std::cout << "Page: " << i << " Dir slot: " << dir_slot << " Record: ";
      std::cout << record << std::endl;
    }
  }
}

void fill_table1(HeapFile& heap_file) {
  // Schema1 = {A: int, B: int, C: str}
  for (int i = 0; i < 5; i++) {
    Value valA(i);
    Value valB(1);
    Value valC("value: " + std::to_string(i + 1));

    std::vector<Value> values = {valA, valB, valC};

    Record record(values);

    heap_file.insert_record(record, 0);
  }
}

void fill_table2(HeapFile& heap_file) {
  // Schema2 = {A: str, B: int, C: int}
  for (int i = 0; i < 256; i++) {
    Value valA("a" + std::to_string(i + 10));
    Value valB(1);
    Value valC(2 * i);

    std::vector<Value> values = {valA, valB, valC};

    Record record(values);

    heap_file.insert_record(record, 0);
  }
}

void fill_table3(HeapFile& heap_file) {
  // Schema 3 = {A: int, B: int, C: int}
  for (int i = 0; i < 9; i++) {
    Value valA(i);
    Value valB(std::to_string(9));
    Value valC(i + 2);

    std::vector<Value> values = {valA, valB, valC};

    Record record(values);

    heap_file.insert_record(record, 0);
  }
}

int main() {
  auto system = System("data/example_db");

  // create schemas:
  Schema schema1({{"A", DataType::INT}, {"B", DataType::INT}, {"C", DataType::STR}});

  Schema schema2({{"A", DataType::STR}, {"B", DataType::INT}, {"C", DataType::INT}});

  // Schema schema3({{"A", DataType::INT}, {"B", DataType::STR}, {"C", DataType::INT}});

  // Table names:
  std::string table_name1 = "r";

  std::string table_name2 = "s";

  // std::string table_name3 = "t";

  // Create tables
  auto table_info1 = catalog.create_table(table_name1, schema1);
  auto table_info2 = catalog.create_table(table_name2, schema2);
  // auto table_info3 = catalog.create_table(table_name3, schema3);
  if (table_info1 == nullptr|| table_info2 == nullptr ) {//|| table_info3 == nullptr) {
    std::cout << "Error creating tables" << std::endl;
    return EXIT_FAILURE;
  }

  // Fill tables with records
  auto table1 = table_info1->heap_file.get();
  auto table2 = table_info2->heap_file.get();
  // auto table3 = table_info3->heap_file.get();

  fill_table1(*table1);
  fill_table2(*table2);
  // fill_table3(*table3);

  std::cout << "Database example_db Created" << std::endl;

  return 0;
}