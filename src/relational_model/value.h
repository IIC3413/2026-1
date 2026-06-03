#pragma once

#include <cassert>
#include <cstdint>
#include <ostream>
#include <string>
#include <variant>

#include "storage/rid.h"

class Value {
public:
  static constexpr int64_t MAX_STRLEN = 255;

  Value(int64_t);

  Value(const std::string&);

  Value(std::string&&);

  Value(RID);

  uint64_t get_hash() const;

  bool operator<(const Value& other) const;
  bool operator==(const Value& other) const;

  bool operator!=(const Value& other) const {
    return !(*this == other);
  }

  bool operator<=(const Value& other) const {
    return !(other < *this);
  }

  bool operator>=(const Value& other) const {
    return !(*this < other);
  }

  bool operator>(const Value& other) const {
    return other < *this;
  }

  Value operator+(const Value& other) const;

  Value operator-(const Value& other) const;

  Value operator*(const Value& other) const;

  Value operator/(const Value& other) const;

  Value operator%(const Value& other) const;

  bool is_string() const {
    return std::holds_alternative<std::string>(value);
  }

  bool is_int() const {
    return std::holds_alternative<int64_t>(value);
  }

  bool is_rid() const {
    return std::holds_alternative<RID>(value);
  }

  RID as_rid() const {
    assert(is_rid());
    return std::get<RID>(value);
  }

  int64_t as_int() const {
    assert(is_int());
    return std::get<int64_t>(value);
  }

  std::string as_string() const {
    assert(is_string());
    return std::get<std::string>(value);
  }

  std::string to_string() const {
    if (is_string()) {
      return '"' + as_string() + '"';
    } else if (is_int()) {
      return std::to_string(as_int());
    }
    return "";
  }

  std::variant<std::string, int64_t, RID> value;

  friend std::ostream& operator<<(std::ostream& os, const Value& v) {
    if (std::holds_alternative<std::string>(v.value)) {
      os << '"' << std::get<std::string>(v.value) << '"';
    } else if (std::holds_alternative<int64_t>(v.value)) {
      os << std::get<int64_t>(v.value);
    } else if (std::holds_alternative<RID>(v.value)) {
      os << std::get<RID>(v.value).page_num << ":" << std::get<RID>(v.value).dir_slot;
    }
    return os;
  }
};
