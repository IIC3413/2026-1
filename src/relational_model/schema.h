#pragma once

#include <cstddef>
#include <string>
#include <vector>

// IIC3413-DB will only support as datatypes:
// - strings
// - 64 bit signed integer
enum class DataType { STR, INT, RID, INVALID };

using TableId = size_t;

struct ColumnInfo {
  std::string name;
  DataType datatype;
  TableId table_id = 0;

  bool operator==(const ColumnInfo& other) const {
    return name == other.name && datatype == other.datatype;
  }
};

class Schema {
public:
  Schema(std::vector<ColumnInfo> columns)
      : columns(std::move(columns)) {}

  Schema() {}

  std::vector<ColumnInfo> columns;

  bool operator==(const Schema& other) const {
    return columns == other.columns;
  }
};
