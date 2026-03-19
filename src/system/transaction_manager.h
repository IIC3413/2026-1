#pragma once

#include <cstdint>
#include <memory>
#include <shared_mutex>

#include "relational_model/transaction.h"
#include "system/tx_id.h"

class TransactionManager {
public:
  TransactionManager() = default;

  ~TransactionManager();

  Transaction start_transaction(IsolationLevel isolation_level);

  TransactionState get_state(TxID tx_id);

  IsolationLevel get_isolation_level(TxID tx_id);

  void commit_transaction(TxID tx_id);

  void abort_transaction(TxID tx_id);

  void add_to_first_rids(TableId table_id, RID rid, TxID tx_id);

  uint64_t get_transaction_count();

  void set_transaction_count(uint64_t count);

private:
  std::shared_mutex active_transaction_mutex;

  std::unordered_map<uint64_t, std::unique_ptr<Transaction>> active_transactions;
};
