#pragma once

#include <cstdint>
#include <mutex>
#include <unordered_map>

#include "relational_model/transaction.h"
#include "storage/rid.h"

struct LockInfo {
  TxID holder_tx_id = 0;

  LockInfo() = default;
  LockInfo(TxID tx_id)
      : holder_tx_id(tx_id) {}
};

class LockManager {
public:
  static constexpr auto MAX_TIME = std::chrono::seconds(10);

  // Only locks the first version of a record
  bool try_acquire_lock(TxID tx_id, uint64_t table_id, RID rid_first);

  void release_lock(TxID tx_id, uint64_t table_id, RID rid);

  void release_all_locks(Transaction& tx);

private:
  std::mutex lock_table_mutex;

  std::unordered_map<TupleKey, LockInfo, TupleKey::Hasher> lock_table;
};
