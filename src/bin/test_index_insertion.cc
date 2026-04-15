#include "iostream"
#include <filesystem>
#include "storage/linear_hash_index/hash_index.h"
#include "system/system.h"

/*
Expected output:

Record: (0,1,"value: 1")
Record: (1,1,"value: 2")
Record: (2,1,"value: 3")
Record: (3,1,"value: 4")
Record: (4,1,"value: 5")

print_index output:

Bucket page [0]: (0,0) | (0,1) | (0,2) | (0,3) | (0,4)
Bucket page [1]:
Bucket page [2]:
Bucket page [3]:
Bucket page [4]:
Bucket page [5]:
Bucket page [6]:
Bucket page [7]:
Bucket page [8]:
Bucket page [9]:
*/

int main() {
  std::filesystem::path dirPath = "data/example_db";
  auto system = System(dirPath);

  std::string table_name = "R";

  auto table_info = catalog.get_table_info(table_name);

  if (table_info == nullptr) {
    std::cout << "Table " << table_name << " does not exist" << std::endl;
    return EXIT_FAILURE;
  }

  std::string dir_file_name = table_info->name + ".dir";
  std::string buckets_file_name = table_info->name + ".hidx";

  FileId dir_file_id = file_mgr.get_file_id(dir_file_name);
  FileId buckets_file_id = file_mgr.get_file_id(buckets_file_name);

  ////////////// Borrando los archivos antiguos del indice ///////////
  buffer_mgr.delete_file(dir_file_id);
  buffer_mgr.delete_file(buckets_file_id);

  dir_file_id = file_mgr.get_file_id(dir_file_name);
  buckets_file_id = file_mgr.get_file_id(buckets_file_name);
  /////////////////////////////////////////////////////////////////////

  auto& heap_file = catalog.get_table_info(table_name)->heap_file;

  size_t N = 10; // buckets iniciales
  int key_col_idx = 1;
  HashIndex hash_index(*heap_file, key_col_idx, dir_file_id, buckets_file_id, N);

  auto iter = heap_file->get_record_iter(TxID(1));
  iter->begin();
  while (!iter->next().invalid()) {
    hash_index.insert_record(iter->get_current_RID());
  }

  // print_index(hash_index);
  // iterando sobre entradas que tiene 1 en la primera columna:
  auto index_iter = hash_index.get_iter(Value(1));
  index_iter->begin();
  auto record = index_iter->next();
  while (!record.invalid()) {
    std::cout << "Record: (" << record.to_string() << ")" << std::endl;
    record = index_iter->next();
  }
}