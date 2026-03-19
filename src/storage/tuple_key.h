#pragma once

#include <cstddef>
#include <cstdint>
#include <functional>

#include "relational_model/schema.h" // TableId
#include "storage/rid.h"

struct TupleKey {
  TableId table_id;
  RID first_rid;

  bool operator==(const TupleKey& other) const {
    return table_id == other.table_id && first_rid == other.first_rid;
  }

  bool operator<(const TupleKey& other) const {
    if (table_id != other.table_id)
      return table_id < other.table_id;
    return first_rid < other.first_rid;
  }

  struct Hasher {
    std::size_t operator()(const TupleKey& key) const noexcept {
      uint64_t packed = (static_cast<uint64_t>(static_cast<uint32_t>(key.first_rid.page_num)) << 32) |
                        static_cast<uint32_t>(key.first_rid.dir_slot);

      std::size_t h1 = std::hash<uint64_t>{}(key.table_id);
      std::size_t h2 = std::hash<uint64_t>{}(packed);

      // hash combine
      return h1 ^ (h2 + 0x9e3779b97f4a7c15ULL + (h1 << 6) + (h1 >> 2));
    }
  };
};
