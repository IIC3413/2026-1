#include "record.h"

Record::Record(const Schema& schema) {
  for (const auto& col : schema.columns) {
    switch (col.datatype) {
    case DataType::RID: {
      break;
    }
    case DataType::INT: {
      values.push_back(Value((int64_t)0));
      break;
    }
    case DataType::STR: {
      values.push_back(Value(""));
      break;
    }
    case DataType::INVALID: {
      assert(false);
      break;
    }
    }
  }
}

Record::Record(const std::vector<DataType> types) {
  for (const auto& type : types) {
    switch (type) {
    case DataType::RID: {
      break;
    }
    case DataType::INT: {
      values.push_back(Value((int64_t)0));
      break;
    }
    case DataType::STR: {
      values.push_back(Value(""));
      break;
    }
    case DataType::INVALID: {
      assert(false);
      break;
    }
    }
  }
}

Record::Record(const std::vector<Value> values)
    : values(values) {}
