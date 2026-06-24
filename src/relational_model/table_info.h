#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>

using TableId = size_t;

class Schema;
class HeapFile;
class Record;

struct TableInfo {
  std::string name;
  std::unique_ptr<Schema> schema;
  std::unique_ptr<HeapFile> heap_file;
  TableId table_id;

  uint64_t cardinality;

  TableInfo(
      const std::string& name,
      std::unique_ptr<Schema> _schema,
      std::unique_ptr<HeapFile> heap_file,
      TableId table_id,
      uint64_t cardinality
  );
};
