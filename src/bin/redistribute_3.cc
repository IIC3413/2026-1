#include "iostream"
#include "storage/linear_hash_index/hash_index.h"
#include "system/system.h"
#include "test_datasets.h"

#include <cstdlib>
#include <filesystem>

/*
Bucket 0: []
Bucket 1: [4,5,4,5]
...
Bucket 0: []
Bucket 1: [4,5,4,5]->[4] <- desencadena split
Bucket 2: [] <- creado por split de Bucket 0
...
Bucket 0: []
Bucket 1: [4,5,4,5]->[4,5,4,5]
Bucket 2: []
...
Bucket 0: []
Bucket 1: [4,5,4,5]->[4,5,4,5]
Bucket 2: [1,1,1,1]->[1] <- desencadena split
Bucket 3: [] <- creado por split de Bucket 1
...
Bucket 0: []
Bucket 1: [4,4,4,4] <- se hizo redistribute de este bucket (queda una página en el garbage collector)
Bucket 2: [1,1,1,1]->[1]
Bucket 3: [5,5,5,5]
*/

int main() {
  std::string table_name = datasets::REDISTRIBUTE_3;
  {
    std::filesystem::path dirPath = "data/example_db";
    auto system = System(dirPath);

    auto table_info = catalog.get_table_info(table_name);

    if (table_info == nullptr) {
      std::cerr << "Reference table not found: " << table_name << std::endl;
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

    size_t N = 2; // buckets iniciales
    int key_col_idx = 1;
    HashIndex hash_index(*heap_file, key_col_idx, dir_file_id, buckets_file_id, N);

    auto iter = heap_file->get_record_iter(TxID(1));
    iter->begin();
    while (!iter->next().invalid()) {
      hash_index.insert_record(iter->get_current_RID());
    }
  }
  // Compare student index against reference
  std::string cmd =
      std::string("build/Debug/bin/compare_index ") + table_name + " --mode multiset --keys 4,5,1";
  std::system(cmd.c_str());
  return EXIT_SUCCESS;
}