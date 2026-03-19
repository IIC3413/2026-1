#include "system/system.h"
#include <iostream>
#include <memory>

#include "storage/heap_file/heap_file.h"
#include "system/catalog.h"
#include "system/system.h"

/*
For the created tables in create_db, the output of this program should be:
Table r:
A, B, C,
0,"value: 0","value 2: 1"
2,"value: 2","value 2: 3"
3,"value: 3","value 2: 4"
4,"value: 4","value 2: 5"
5,"value: 5","value 2: 6"
6,"value: 6","value 2: 7"
7,"value: 7","value 2: 8"
8,"value: 8","value 2: 9"
9,"value: 9","value 2: 10"
1,"updated_value","updated_value"

Table s:
A, B, C,
"a: 0","b: 10",0
"a: 2","b: 12",4
"a: 0","b: 13",6
"a: 1","b: 14",8
"a: 2","b: 15",10
"a: 0","b: 16",12
"a: 1","b: 17",14
"a: 2","b: 18",16
"a: 0","b: 19",18
"a: 1","b: 20",20
"a: 2","b: 21",22
"a: 0","b: 22",24
"a: 1","b: 23",26
"a: 2","b: 24",28
"updated_value","updated_value",1

Table t:
A, B, C,
0,1,2
2,3,4
3,4,5
4,5,6
5,6,7
6,7,8
7,8,9
8,9,10
1,1,1
*/

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "Usage: test_update <table_name> <args...>" << std::endl;
    return EXIT_FAILURE;
  }
  auto system = System("data/example_db");

  Value val1(1);
  Value val2("updated_value");

  std::string table_name = argv[1];

  auto table_info = catalog.get_table_info(table_name);
  if (table_info == nullptr) {
    std::cout << "Table " << table_name << " does not exist" << std::endl;
    return EXIT_FAILURE;
  }

  std::vector<Value> new_values;

  for (const auto& col : table_info->schema->columns) {
    switch (col.datatype) {
    case DataType::INT:
      new_values.push_back(val1);
      break;
    case DataType::STR:
      new_values.push_back(val2);
      break;
    case DataType::RID:
      break;
    case DataType::INVALID:
      break;
    }
  }

  Record new_record(new_values);

  auto table = table_info->heap_file.get();

  auto out_rid = table->update(RID(0, 1), new_record, 1);

  if (out_rid == RID(-1, -2)) {
    std::cout << "try to update record deleted" << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "Update test completed successfully" << std::endl;

  return 0;
}