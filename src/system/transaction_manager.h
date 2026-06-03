#pragma once

#include "relational_model/transaction.h"
#include "system/tx_id.h"

#include <cstdint>
#include <memory>
#include <shared_mutex>


class TransactionManager {
public:
  TransactionManager() = default;

  ~TransactionManager();

  TxID start_transaction(IsolationLevel isolation_level);

  TransactionState get_state(TxID tx_id);

  // Return the states of two transactions while holding the
  // shared lock once (avoids races when checking two tx states).
  std::pair<TransactionState, TransactionState> get_states(TxID tx_id_a, TxID tx_id_b);

  IsolationLevel get_isolation_level(TxID tx_id);

  void commit_transaction(TxID tx_id);

  void abort_transaction(TxID tx_id);

  void add_to_write_set(TableId table_id, RID rid, TxID tx_id);

  uint64_t get_transaction_count();

  void set_transaction_count(uint64_t count);

  bool was_active_at_snapshot(TxID reader, TxID writer);

private:
  std::shared_mutex active_transaction_mutex;

  std::unordered_map<uint64_t, std::unique_ptr<Transaction>> active_transactions;

  void _abort_transaction(Transaction* transaction, TxID tx_id);
};
