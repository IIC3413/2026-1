#include "system/system.h"

#include <cstdint>
#include <mutex>
#include <thread>

#include "exceptions/exceptions.h"

bool LockManager::try_acquire_lock(TxID tx_id, uint64_t table_id, RID first_rid) {
  TupleKey key{table_id, first_rid};

  // uint8_t tries = 0;
  auto start = std::chrono::steady_clock::now();
  while (true) {
    // if (tries == MAX_TRIES) {
    //   // abort transaction
    //   transaction_mgr.abort_transaction(tx_id);
    //   return false;
    // }
    auto time_elapsed = std::chrono::steady_clock::now() - start;
    if (time_elapsed > MAX_TIME) {
      transaction_mgr.abort_transaction(tx_id);
      throw LockException("Transaction " + std::to_string(tx_id) + " aborted due to lock timeout");
    }
    {
      std::lock_guard<std::mutex> guard(lock_table_mutex);
      auto it = lock_table.find(key);
      if (it == lock_table.end()) {
        lock_table.emplace(key, tx_id);
        // std::cout << "[Lock Manager] Lock acquired by tx_id: " << tx_id << " (page=" << first_rid.page_num
        //           << ", slot=" << first_rid.dir_slot << ") " << std::endl;
        return true;
      } else {
        if (it->second.holder_tx_id == tx_id) {
          // already have the lock
          return true;
        }
      }
      //  tries++;
    } // scope of the mutex

    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // wait before retrying
  }
  return false;
}

// Transaction used strict 2PL, so all locks are released at commit/abort time
void LockManager::release_all_locks(Transaction& tx) {
  std::lock_guard<std::mutex> guard(lock_table_mutex);
  const std::set<TupleKey>& to_release = tx.get_first_rids();
  for (const TupleKey& key : to_release) {
    auto it = lock_table.find(key);
    // std::cout << "[Lock Manager] Lock released by tx_id: " << tx.get_id() << " (page=" <<
    // key.first_rid.page_num
    //           << ", slot=" << key.first_rid.dir_slot << ") " << std::endl;
    if (it != lock_table.end() && it->second.holder_tx_id == tx.get_id()) {
      lock_table.erase(it);
    }
  }
}
