#include <iostream>
#include <mutex>
#include <stdexcept>

#include "exceptions/exceptions.h"
#include "relational_model/transaction.h"
#include "system/system.h"
#include "transaction_manager.h"

TransactionManager::~TransactionManager() {
  std::unique_lock lock(active_transaction_mutex);
  for (auto& [tx_id, transaction] : active_transactions) {
    if (transaction->state == TransactionState::COMMITTED)
      continue;

    transaction->abort();
    lock_mgr.release_all_locks(*transaction);
    catalog.abort_in_progress_tables(tx_id);
    transaction->set_state(TransactionState::COMMITTED);
  }
  active_transactions.clear();
}

TxID TransactionManager::start_transaction(IsolationLevel isolation_level) {
  std::unique_lock lock(active_transaction_mutex);
  auto tx_id = catalog.update_transaction_count();

  auto tx = std::make_unique<Transaction>(tx_id, isolation_level);
  tx->state = TransactionState::ACTIVE;

  if (isolation_level == IsolationLevel::SNAPSHOT_ISOLATION) {
    for (const auto& [active_tx_id, active_transaction] : active_transactions) {
      if (active_transaction->state == TransactionState::COMMITTED)
        continue;

      tx->snapshot.insert(active_tx_id);
    }
  }

  active_transactions.insert({tx_id, std::move(tx)});
  return tx_id;
}

// TransactionState TransactionManager::get_state(TxID tx_id) {
//   std::shared_lock lock(active_transaction_mutex);

//   auto it = active_transactions.find(tx_id);

//   if (it == active_transactions.end()) {
//     return TransactionState::COMMITTED;
//   }

//   return it->second->state;
// }

std::pair<TransactionState, TransactionState> TransactionManager::get_states(TxID tx_id_a, TxID tx_id_b) {
  std::shared_lock lock(active_transaction_mutex);

  TransactionState state_a;
  TransactionState state_b;

  auto it_a = active_transactions.find(tx_id_a);
  if (it_a == active_transactions.end()) {
    state_a = TransactionState::COMMITTED;
  } else {
    state_a = it_a->second->state;
  }

  auto it_b = active_transactions.find(tx_id_b);
  if (it_b == active_transactions.end()) {
    state_b = TransactionState::COMMITTED;
  } else {
    state_b = it_b->second->state;
  }

  return {state_a, state_b};
}

IsolationLevel TransactionManager::get_isolation_level(TxID tx_id) {
  std::shared_lock lock(active_transaction_mutex);
  auto it = active_transactions.find(tx_id);
  if (it == active_transactions.end()) {
    throw std::runtime_error("Transaction ID not found");
  }
  return it->second->get_isolation_level();
}

void TransactionManager::commit_transaction(TxID tx_id) {
  Transaction* transaction;
  {
    std::unique_lock lock(active_transaction_mutex);
    auto it = active_transactions.find(tx_id);
    if (it == active_transactions.end()) {
      std::string msg = "[COMMIT] Transaction " + std::to_string(tx_id) + " not found";
      throw std::runtime_error(msg);
    }
    transaction = it->second.get();
  }
  if (transaction->state != TransactionState::ACTIVE) {
    throw std::runtime_error("Transaction not active");
  }

  try {
    catalog.commit_in_progress_tables(tx_id);
    transaction->state = TransactionState::COMMITTED;

    // release locks only after the transaction is fully committed,
    // so other transactions always see a consistent state
    lock_mgr.release_all_locks(*transaction);
    {
      std::unique_lock lock(active_transaction_mutex);
      active_transactions.erase(tx_id);
    }
  } catch (TransactionAbortException& e) {
    // Do not call abort_transaction() here.
    // commit_transaction() already holds active_transaction_mutex,
    // and abort_transaction() would try to acquire it again,
    // causing a self-deadlock on commit failure

    // Abort transaction inline while still holding
    // active_transaction_mutex
    _abort_transaction(transaction, tx_id);
    {
      std::unique_lock lock(active_transaction_mutex);
      active_transactions.erase(tx_id);
    }
    throw;
  }
}

void TransactionManager::abort_transaction(TxID tx_id) {
  Transaction* transaction;

  std::cerr << "[TransactionManager] abort_transaction called for tx " << tx_id << std::endl;
  {
    std::unique_lock lock(active_transaction_mutex);
    auto it = active_transactions.find(tx_id);
    if (it == active_transactions.end()) {
      std::string msg = "[ABORT] Transaction " + std::to_string(tx_id) + " not found";
      std::cerr << "[TransactionManager] abort_transaction failed: " << msg << std::endl;
      throw std::runtime_error(msg);
    }
    transaction = it->second.get();
  }

  // Undo changes made by this transaction
  _abort_transaction(transaction, tx_id);

  {
    // we did not reuse the previous lock because some methods are heavy and we dont
    // want to lock active_transaction_mutex too long
    std::unique_lock lock(active_transaction_mutex);
    active_transactions.erase(tx_id);
  }
  std::cerr << "[TransactionManager] abort_transaction finished for tx " << tx_id << std::endl;
}

void TransactionManager::add_to_write_set(TableId table_id, RID rid, TxID tx_id) {
  std::shared_lock lock(active_transaction_mutex);
  auto it = active_transactions.find(tx_id);
  if (it == active_transactions.end()) {
    std::string msg = "[ADD_ACTIVE_TX] Transaction " + std::to_string(tx_id) + " not found";
    throw std::runtime_error(msg);
  }
  Transaction& transaction = *it->second;
  // shouldn't be two threads adding RIDs to the same transaction set at the same time.
  transaction.first_rids.insert(TupleKey{table_id, rid});
}

// Returns whether the writer transaction was active
// at the moment the reader transaction created its snapshot.
bool TransactionManager::was_active_at_snapshot(TxID reader, TxID writer) {
  if (reader == writer)
    return false;

  std::shared_lock lock(active_transaction_mutex);
  auto it = active_transactions.find(reader);
  if (it != active_transactions.end()) {
    Transaction& transaction = *it->second;
    return transaction.was_active_at_snapshot(writer);
  }
  return false;
}

void TransactionManager::_abort_transaction(Transaction* transaction, TxID tx_id) {
  transaction->abort();
  catalog.abort_in_progress_tables(tx_id);
  transaction->set_state(TransactionState::COMMITTED);
  lock_mgr.release_all_locks(*transaction);
}
