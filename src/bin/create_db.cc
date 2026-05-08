#include <iostream>
#include <memory>
#include <random>

#include "relational_model/record.h"
#include "relational_model/schema.h"
#include "relational_model/value.h"
#include "storage/heap_file/heap_file.h"
#include "system/catalog.h"
#include "system/system.h"
#include "test_datasets.h"

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
  for (int i = 0; i < 256; i++) {
    Value valA(i);
    Value valB(0);
    Value valC("value: " + std::to_string(i + 1));

    std::vector<Value> values = {valA, valB, valC};

    Record record(values);

    heap_file.insert_record(record, 0);
  }
}

void fill_table2(HeapFile& heap_file) {
  // Schema2 = {A: str, B: int, C: int}
  for (int i = 0; i < 511; i++) {
    Value valA("a" + std::to_string(i + 10));
    Value valB(3);
    Value valC(2 * i);

    std::vector<Value> values = {valA, valB, valC};

    Record record(values);

    heap_file.insert_record(record, 0);
  }
}

void fill_table4(HeapFile& heap_file) {
  // Schema 4 = {A: int, B: int, C: int}
  Value valA(1);
  Value valB(0);
  Value valC(3);

  std::vector<Value> values = {valA, valB, valC};

  Record record(values);

  heap_file.insert_record(record, 0);
}

void fill_table5(HeapFile& heap_file) {
  // Schema 4 = {A: int, B: int, C: int}
  for (int i = 0; i < 30; i++) {
    Value valA(i);
    Value valB(0);
    Value valC(i + 2);

    std::vector<Value> values = {valA, valB, valC};

    Record record(values);

    heap_file.insert_record(record, 0);
  }
}

void fill_table6(HeapFile& heap_file) {
  // Schema 4 = {A: int, B: int, C: int}
  for (int i = 0; i < 10; i++) {
    Value valA(i);
    Value valB(0);
    Value valC(i + 2);

    std::vector<Value> values = {valA, valB, valC};

    Record record(values);

    heap_file.insert_record(record, 0);
  }
}


void fill_table7(HeapFile& heap_file) {
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

void fill_table8(HeapFile& heap_file) {
  // Schema 4 = {A: int, B: int, C: int}
  for (int i = 0; i < 100000; i++) {
    Value valA(i);
    Value valB(1);
    Value valC(i + 2);

    std::vector<Value> values = {valA, valB, valC};

    Record record(values);

    heap_file.insert_record(record, 0);
  }
}

void fill_table9(HeapFile& heap_file) {
  // Schema 4 = {A: int, B: int, C: int}
  for (int i = 0; i < 756; i++) {
    Value valA(i);
    Value valB = 1;
    if (i < 510) {
      valB = (i % 2) == 0 ? 4 : 5;
    }
    Value valC(i + 2);

    std::vector<Value> values = {valA, valB, valC};

    Record record(values);

    heap_file.insert_record(record, 0);
  }
}

void fill_table11(HeapFile& heap_file) {
  // Schema 4 = {A: int, B: int, C: int}
  for (int i = 0; i < 256; i++) {
    Value valA(i);
    Value valB(1);
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

  Schema schema4({{"A", DataType::INT}, {"B", DataType::INT}, {"C", DataType::INT}});

  Schema schema5({{"A", DataType::INT}, {"B", DataType::INT}, {"C", DataType::INT}});

  Schema schema6({{"A", DataType::INT}, {"B", DataType::INT}, {"C", DataType::INT}});

  Schema schema7({{"A", DataType::STR}, {"B", DataType::INT}, {"C", DataType::INT}});

  Schema schema8({{"A", DataType::INT}, {"B", DataType::INT}, {"C", DataType::INT}});

  Schema schema9({{"A", DataType::INT}, {"B", DataType::INT}, {"C", DataType::INT}});

  Schema schema11({{"A", DataType::INT}, {"B", DataType::INT}, {"C", DataType::INT}});

  // Table names:
  std::string table_name1 = datasets::INSERT_1;

  std::string table_name2 = datasets::INSERT_2;

  std::string table_name4 = datasets::DELETE_1;

  std::string table_name5 = datasets::DELETE_2;

  std::string table_name6 = datasets::DELETE_3;

  std::string table_name7 = datasets::REDISTRIBUTE_1;

  std::string table_name8 = datasets::REDISTRIBUTE_2;

  std::string table_name9 = datasets::REDISTRIBUTE_3;

  std::string table_name11 = datasets::REDISTRIBUTE_4;


  // Create tables
  auto table_info1 = catalog.create_table(table_name1, schema1);
  auto table_info2 = catalog.create_table(table_name2, schema2);
  auto table_info4 = catalog.create_table(table_name4, schema4);
  auto table_info5 = catalog.create_table(table_name5, schema5);
  auto table_info6 = catalog.create_table(table_name6, schema6);
  auto table_info7 = catalog.create_table(table_name7, schema7);
  auto table_info8 = catalog.create_table(table_name8, schema8);
  auto table_info9 = catalog.create_table(table_name9, schema9);
  auto table_info11 = catalog.create_table(table_name11, schema11);


  if (table_info1 == nullptr || table_info2 == nullptr || table_info4 == nullptr ||
      table_info5 == nullptr || table_info6 == nullptr || table_info7 == nullptr ||
      table_info8 == nullptr || table_info9 == nullptr ||
      table_info11 == nullptr) {
    std::cout << "Error creating tables" << std::endl;
    return EXIT_FAILURE;
  }

  // Fill tables with records
  auto table1 = table_info1->heap_file.get();
  auto table2 = table_info2->heap_file.get();
  auto table4 = table_info4->heap_file.get();
  auto table5 = table_info5->heap_file.get();
  auto table6 = table_info6->heap_file.get();
  auto table7 = table_info7->heap_file.get();
  auto table8 = table_info8->heap_file.get();
  auto table9 = table_info9->heap_file.get();
  auto table11 = table_info11->heap_file.get();


  fill_table1(*table1);
  fill_table2(*table2);
  fill_table4(*table4);
  fill_table5(*table5);
  fill_table6(*table6);
  fill_table7(*table7);
  fill_table8(*table8);
  fill_table9(*table9);
  fill_table11(*table11);


  std::cout << "Database example_db Created" << std::endl;

  return 0;
}