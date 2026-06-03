#pragma once

#include <cstdint>
#include <ostream>
#include <vector>

#include "relational_model/schema.h"
#include "relational_model/value.h"

class Record {
public:
  std::vector<Value> values;

  Record() = default;

  Record(const Schema& schema);

  Record(std::vector<DataType> types);

  Record(const Record& other) = default;

  Record(const std::vector<Value> other);

  bool invalid() const {
    return values.empty();
  }

  friend std::ostream& operator<<(std::ostream& os, const Record& o) {
    char separator[2] = {'\0', '\0'};
    for (unsigned i = 0; i < o.values.size(); i++) {
      os << separator;
      os << o.values[i];
      separator[0] = ',';
    }
    return os;
  }

  std::string to_string() const {
    std::string result;
    char separator[2] = {'\0', '\0'};
    for (unsigned i = 0; i < values.size(); i++) {
      result += separator;
      result += values[i].to_string();
      separator[0] = ',';
    }
    return result;
  }

  Record& operator=(const Record& other) = default;

  bool operator==(const Record& other) const {
    return this->values == other.values;
  }

  uint64_t hash() {
    Hasher hasher;
    return hasher.operator()(*this);
  }

  struct Hasher {
    uint64_t operator()(const Record& record) const {
      uint64_t res = 0;
      for (const auto& value : record.values) {
        res ^= value.get_hash();
      }
      return res;
    }
  };
};
