#include "system/system.h"
#include <iostream>
#include <memory>

#include "relational_model/schema.h"
#include "storage/linear_hash_index/hash_index.h"
#include "storage/linear_hash_index/hash_index_bucket.h"
#include "system/catalog.h"
#include "system/system.h"

void print_rids(HashIndex& hash_index) {
  auto total_pages = file_mgr.count_pages(hash_index.buckets_file_id);
  //  std::cout << "Total pages: " << total_pages << std::endl;
  for (auto p = 0; p < total_pages; p++) {
    auto page = std::make_unique<BucketPage>(hash_index, p);
    std::cout << "Bucket page [" << p <<"]: ";
    for (int i = 0; i < page->get_tuple_count(); i++) {
      auto index_record = page->get_record(i);
      std::cout << "("<< index_record.rid.page_num <<","<<index_record.rid.dir_slot<< ")";
      if (i != page->get_tuple_count() - 1) {
        std::cout << " | ";
      }
    }
    std::cout << "\n";
  }
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "Usage: .../print_index <table_name>" << std::endl;
    return EXIT_FAILURE;
  }
  auto system = System("data/example_db");

  std::string table_name = argv[1];

  auto table_info = catalog.get_table_info(table_name);

  if (table_info == nullptr) {
    std::cout << "Table " << table_name << " does not exist" << std::endl;
    return EXIT_FAILURE;
  }

  std::string dir_file_name = table_info->name + ".dir";
  std::string buckets_file_name = table_info->name + ".hidx";

  FileId dir_file_id = file_mgr.get_file_id(dir_file_name);
  FileId buckets_file_id = file_mgr.get_file_id(buckets_file_name);

  auto& heap_file = catalog.get_table_info(table_name)->heap_file;

  int key_col_idx = 1;
  HashIndex hash_index(*heap_file, key_col_idx, dir_file_id, buckets_file_id);

  print_rids(hash_index);

  return 0;
}