#pragma once

#include <cstdint>

struct RID {
  int32_t page_num;
  int32_t dir_slot;

  RID() {}

  RID(int32_t page_num, int32_t dir_slot)
      : page_num(page_num),
        dir_slot(dir_slot) {}

  bool operator==(const RID& other) const {
    return page_num == other.page_num && dir_slot == other.dir_slot;
  }

  bool operator!=(const RID& other) const {
    return !(*this == other);
  }

  bool operator<(const RID& other) const {
    if (page_num < other.page_num) {
      return true;
    } else if (other.page_num < page_num) {
      return false;
    }

    return dir_slot < other.dir_slot;
  }
};
