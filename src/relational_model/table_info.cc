#include "table_info.h"

#include "relational_model/schema.h"
#include "storage/heap_file/heap_file.h"

TableInfo::TableInfo(
    const std::string& name,
    std::unique_ptr<Schema> _schema,
    std::unique_ptr<HeapFile> heap_file,
    TableId table_id,
    uint64_t cardinality,
    std::vector<std::unique_ptr<Index>> indexes
)
    : name(name),
      schema(std::move(_schema)),
      heap_file(std::move(heap_file)),
      table_id(table_id),
      cardinality(cardinality) {
        if (!indexes.empty()) {
            this->indexes = std::move(indexes);
        }
      }
