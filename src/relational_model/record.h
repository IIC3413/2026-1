#pragma once

#include <cstdint>
#include <ostream>
#include <vector>
#include <cstring>

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

  uint64_t get_size_for_serialize() const {
    size_t needed_record_size = 0;
    for (size_t i = 0; i < values.size(); i++) {
      const auto& value = values[i];
      if (value.is_string()) {
        needed_record_size += sizeof(uint8_t) + value.as_string().size();
      } else if (value.is_int()) {
        needed_record_size += sizeof(int64_t);
      }
    }
    return needed_record_size;
  }

  // this assumes have enough space to write this record
  void serialize(char* out) const {
    for (auto& value : values) {
      if (value.is_string()) {
        auto& s = value.as_string();
        uint8_t size = s.size();

        memcpy(out, &size, sizeof(uint8_t));
        out += sizeof(uint8_t);

        memcpy(out, value.as_string().data(), size);
        out += size;

      } else if (value.is_int()) {
        int64_t i = value.as_int();
        memcpy(out, &i, sizeof(int64_t));
        out += sizeof(int64_t);
      }
    }
  }

  static Record deserialize(const char* in, std::vector<DataType> datatypes) {
    Record record;
    for (auto datatype : datatypes) {
      if (datatype == DataType::INT) {
        int64_t res;
        memcpy(&res, in, sizeof(int64_t));
        record.values.push_back(res);
        in += sizeof(int64_t);
      } else if (datatype == DataType::STR) {
        uint8_t size = *(reinterpret_cast<const uint8_t*>(in));
        in += sizeof(uint8_t);

        std::string res(in, size);
        record.values.push_back(res);

        in += size;
      } else {
        throw std::runtime_error("Unsupported type in deserialization");
      }
    }
    return record;
  }

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
