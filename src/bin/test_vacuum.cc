
#include "storage/heap_file/heap_file.h"
#include "system/system.h"
#include <iostream>
#include <memory>

// This test assumes that there is a record with RID (0, 0) on table
/* When table it's printed it should appear something like this for table r:
A, B, C,

1,"value: 1","value 2: 2"
2,"value: 2","value 2: 3"
3,"value: 3","value 2: 4"
4,"value: 4","value 2: 5"
5,"value: 5","value 2: 6"
6,"value: 6","value 2: 7"
7,"value: 7","value 2: 8"
8,"value: 8","value 2: 9"
9,"value: 9","value 2: 10"

Where the record with RID(0, 0) it's deleted (the first empty row).
Make sure to view the bytes of the file to check that the record does not exist.

*/

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "Usage: test_vacuum <table_name> <args...>" << std::endl;
    return EXIT_FAILURE;
  }
  auto system = System("data/example_db");

  std::string table_name = argv[1];

  auto table_info = catalog.get_table_info(table_name);

  if (table_info == nullptr) {
    std::cout << "Table " << table_name << " does not exist" << std::endl;
    return EXIT_FAILURE;
  }

  auto table = table_info->heap_file.get();

  // delete record with RID (0, 0):

  table->delete_record(RID(0, 0), TxID(1));

  table->vacuum();

  return 0;
}
