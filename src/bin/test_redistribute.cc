#include "iostream"
#include <filesystem>
#include "storage/linear_hash_index/hash_index.h"
#include "system/system.h"

/*
Expected output:

Record: ("a10",1,0), record count: 1
Record: ("a11",1,2), record count: 2
                .
                .
                .
Record: ("a262",1,504), record count: 253
Record: ("a263",1,506), record count: 254
Record: ("a264",1,508), record count: 255
Record: ("a265",1,510), record count: 256

print_index output:

Bucket page [0]:
Bucket page [1]:
Bucket page [2]:
Bucket page [3]:
Bucket page [4]:
Bucket page [5]:
Bucket page [6]:
Bucket page [7]:
Bucket page [8]:
Bucket page [9]:
Bucket page [10]:
Bucket page [11]: (0,0) | (0,1) | (0,2) | (0,3) | (0,4) | (0,5) | (0,6) | (0,7) | (0,8) | (0,9) | (0,10) |
(0,11) | (0,12) | (0,13) | (0,14) | (0,15) | (0,16) | (0,17) | (0,18) | (0,19) | (0,20) | (0,21) | (0,22) |
(0,23) | (0,24) | (0,25) | (0,26) | (0,27) | (0,28) | (0,29) | (0,30) | (0,31) | (0,32) | (0,33) | (0,34) |
(0,35) | (0,36) | (0,37) | (0,38) | (0,39) | (0,40) | (0,41) | (0,42) | (0,43) | (0,44) | (0,45) | (0,46) |
(0,47) | (0,48) | (0,49) | (0,50) | (0,51) | (0,52) | (0,53) | (0,54) | (0,55) | (0,56) | (0,57) | (0,58) |
(0,59) | (0,60) | (0,61) | (0,62) | (0,63) | (0,64) | (0,65) | (0,66) | (0,67) | (0,68) | (0,69) | (0,70) |
(0,71) | (0,72) | (1,0) | (1,1) | (1,2) | (1,3) | (1,4) | (1,5) | (1,6) | (1,7) | (1,8) | (1,9) | (1,10) |
(1,11) | (1,12) | (1,13) | (1,14) | (1,15) | (1,16) | (1,17) | (1,18) | (1,19) | (1,20) | (1,21) | (1,22) |
(1,23) | (1,24) | (1,25) | (1,26) | (1,27) | (1,28) | (1,29) | (1,30) | (1,31) | (1,32) | (1,33) | (1,34) |
(1,35) | (1,36) | (1,37) | (1,38) | (1,39) | (1,40) | (1,41) | (1,42) | (1,43) | (1,44) | (1,45) | (1,46) |
(1,47) | (1,48) | (1,49) | (1,50) | (1,51) | (1,52) | (1,53) | (1,54) | (1,55) | (1,56) | (1,57) | (1,58) |
(1,59) | (1,60) | (1,61) | (1,62) | (1,63) | (1,64) | (1,65) | (1,66) | (1,67) | (1,68) | (1,69) | (1,70) |
(1,71) | (2,0) | (2,1) | (2,2) | (2,3) | (2,4) | (2,5) | (2,6) | (2,7) | (2,8) | (2,9) | (2,10) | (2,11) |
(2,12) | (2,13) | (2,14) | (2,15) | (2,16) | (2,17) | (2,18) | (2,19) | (2,20) | (2,21) | (2,22) | (2,23) |
(2,24) | (2,25) | (2,26) | (2,27) | (2,28) | (2,29) | (2,30) | (2,31) | (2,32) | (2,33) | (2,34) | (2,35) |
(2,36) | (2,37) | (2,38) | (2,39) | (2,40) | (2,41) | (2,42) | (2,43) | (2,44) | (2,45) | (2,46) | (2,47) |
(2,48) | (2,49) | (2,50) | (2,51) | (2,52) | (2,53) | (2,54) | (2,55) | (2,56) | (2,57) | (2,58) | (2,59) |
(2,60) | (2,61) | (2,62) | (2,63) | (2,64) | (2,65) | (2,66) | (2,67) | (2,68) | (2,69) | (2,70) | (3,0) |
(3,1) | (3,2) | (3,3) | (3,4) | (3,5) | (3,6) | (3,7) | (3,8) | (3,9) | (3,10) | (3,11) | (3,12) | (3,13) |
(3,14) | (3,15) | (3,16) | (3,17) | (3,18) | (3,19) | (3,20) | (3,21) | (3,22) | (3,23) | (3,24) | (3,25) |
(3,26) | (3,27) | (3,28) | (3,29) | (3,30) | (3,31) | (3,32) | (3,33) | (3,34) | (3,35) | (3,36) | (3,37) |
(3,38)
Bucket page [12]: (3,39)
*/

int main() {
  std::filesystem::path dirPath = "data/example_db";
  auto system = System(dirPath);

  std::string table_name = "S";

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
  //////////////////////////////////////////////////////////////////////

  auto& heap_file = catalog.get_table_info(table_name)->heap_file;

  size_t N = 10; // buckets iniciales
  int key_col_idx = 1;
  HashIndex hash_index(*heap_file, key_col_idx, dir_file_id, buckets_file_id, N);

  auto iter = heap_file->get_record_iter(TxID(0));
  iter->begin();
  while (!iter->next().invalid()) {
    hash_index.insert_record(iter->get_current_RID());
  }

  // iterando sobre entradas que tiene 1 en la primera columna:
  auto index_iter = hash_index.get_iter(Value(1));
  index_iter->begin();
  int i = 1;
  auto record = index_iter->next();
  while (!record.invalid()) {
    std::cout << "Record: (" << record.to_string() << "), record count: "<< i++ << std::endl;
    record = index_iter->next();
  }
}