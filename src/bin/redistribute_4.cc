#include "iostream"
#include "storage/linear_hash_index/hash_index.h"
#include "system/system.h"
#include "test_datasets.h"

#include <cstdlib>
#include <filesystem>

int main() {
  std::string table_name = datasets::REDISTRIBUTE_4;
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

    // Remove old index files if present
    buffer_mgr.delete_file(dir_file_id);
    buffer_mgr.delete_file(buckets_file_id);

    dir_file_id = file_mgr.get_file_id(dir_file_name);
    buckets_file_id = file_mgr.get_file_id(buckets_file_name);

    auto& heap_file = catalog.get_table_info(table_name)->heap_file;

    size_t N = 10; // initial buckets
    int key_col_idx = 1;
    HashIndex hash_index(*heap_file, key_col_idx, dir_file_id, buckets_file_id, N);

    // Insert all records from table into the hash index
    auto iter = heap_file->get_record_iter(TxID(1));
    iter->begin();
    while (!iter->next().invalid()) {
      hash_index.insert_record(iter->get_current_RID());
      hash_index.insert_record(RID(0, 1));
    }
  }
  // Use compare_index to compare multiset of key 1
  std::string cmd = std::string("build/Debug/bin/compare_index ") + table_name + " --mode multiset --keys 1";
  std::system(cmd.c_str());
  return EXIT_SUCCESS;
}
