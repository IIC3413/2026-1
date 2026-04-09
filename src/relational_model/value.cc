#include "value.h"
#include "exceptions/exceptions.h"
#include "third_party/murmur3/murmur3.h"

Value::Value(int64_t i)
    : value(i) {}

Value::Value(const std::string& str_value)
    : value(str_value) {
  assert(str_value.size() <= MAX_STRLEN);
}

Value::Value(std::string&& str_value)
    : value(std::move(str_value)) {
  assert(str_value.size() <= MAX_STRLEN);
}

Value::Value(RID rid)
    : value(rid) {}

uint64_t Value::get_hash() const {
  uint64_t _hash[2];
  if (is_int()) {
    auto a = as_int();
    MurmurHash3_x64_128(&a, sizeof(a), 0, _hash);
  } else if (is_string()) {
    auto s = as_string();
    MurmurHash3_x64_128(s.data(), s.length(), 0, _hash);
  }
  return _hash[0];
}

bool Value::operator<(const Value& other) const {
  return value < other.value;
}

bool Value::operator==(const Value& other) const {
  return value == other.value;
}

Value Value::operator+(const Value& other) const {
  if (!is_int() || !other.is_int()) {
    throw QueryException("Incompatible types for sum");
  }
  return Value(as_int() + other.as_int());
}

Value Value::operator-(const Value& other) const {
  if (!is_int() || !other.is_int()) {
    throw QueryException("Incompatible types for subtraction");
  }
  return Value(as_int() - other.as_int());
}

Value Value::operator*(const Value& other) const {
  if (!is_int() || !other.is_int()) {
    throw QueryException("Incompatible types for multiplication");
  }
  return Value(as_int() * other.as_int());
}

Value Value::operator/(const Value& other) const {
  if (!is_int() || !other.is_int()) {
    throw QueryException("Incompatible types for division");
  }
  if (other.as_int() == 0) {
    throw QueryException("Division by zero");
  }
  return Value(as_int() / other.as_int());
}

Value Value::operator%(const Value& other) const {
  if (!is_int() || !other.is_int()) {
    throw QueryException("Incompatible types for modulo");
  }
  if (other.as_int() == 0) {
    throw QueryException("Modulo by zero");
  }
  return Value(as_int() % other.as_int());
}
