#pragma once

#include "storage/rid.h"

class RecordHeader {
public:
  RecordHeader(uint64_t t_min, uint64_t t_max, RID next, RID first) :
        t_min(t_min),
        t_max(t_max),
        next(next),
        first(first) {}

  uint64_t t_min;
  uint64_t t_max;
  RID next;
  RID first;

  // true if deleted logically or physically
  bool invalid = false;

  RecordHeader()
      : invalid(true) {};

  bool is_invalid() const {
    return invalid;
  }
};
