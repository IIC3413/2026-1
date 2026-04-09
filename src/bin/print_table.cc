#include "system/system.h"
#include <iostream>
#include <memory>

#include "relational_model/schema.h"
#include "storage/heap_file/heap_file.h"
#include "system/catalog.h"
#include "system/system.h"

void print_records(const HeapFile& heap_file) {
  auto total_pages = file_mgr.count_pages(heap_file.file_id);
  //  std::cout << "Total pages: " << total_pages << std::endl;
  for (auto i = 0; i < total_pages; i++) {
    auto page = std::make_unique<HeapFilePage>(heap_file, i);
    for (int dir_slot = 0; dir_slot < page->get_dir_count(); dir_slot++) {
      if (page->get_dir(dir_slot) <= 0) {
        continue;
      }
      auto final_rid = heap_file.get_last_version(RID(i, dir_slot));
      auto page_of_record = std::make_unique<HeapFilePage>(heap_file, final_rid.page_num);
      auto record = page_of_record->get_record(final_rid.dir_slot);
      if (final_rid == RID(i, dir_slot)) {
        std::cout << record << std::endl;
      }
    }
  }
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "Usage: .../print_table <table_name>" << std::endl;
    return EXIT_FAILURE;
  }
  auto system = System("data/example_db");

  std::string table_name = argv[1];

  auto table_info = catalog.get_table_info(table_name);

  if (table_info == nullptr) {
    std::cout << "Table " << table_name << " does not exist" << std::endl;
    return EXIT_FAILURE;
  }

  for (const auto& col : table_info->schema->columns) {
    if (col.datatype == DataType::RID) {
      break;
    }
    std::cout << col.name << ", ";
  }
  std::cout << std::endl;

  print_records(*(table_info->heap_file));

  return 0;
}