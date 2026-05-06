#include <mutex>
#include <stdexcept>

#include "relational_model/transaction.h"
#include "system/system.h"
#include "transaction_manager.h"

TransactionManager::~TransactionManager() {
  std::unique_lock lock(active_transaction_mutex);
  for (auto& [tx_id, transaction] : active_transactions) {
    transaction->abort();
    lock_mgr.release_all_locks(*transaction);
    catalog.abort_in_progress_tables(tx_id);
    transaction->set_state(TransactionState::COMMITTED);
  }
  active_transactions.clear();
}

Transaction TransactionManager::start_transaction(IsolationLevel isolation_level) {
  auto tx_id = catalog.update_transaction_count();

  std::unique_lock lock(active_transaction_mutex);
  auto tx = std::make_unique<Transaction>(tx_id, isolation_level);
  tx->state = TransactionState::ACTIVE;
  active_transactions.insert({tx_id, std::move(tx)});
  return *(active_transactions[tx_id]);
}

TransactionState TransactionManager::get_state(TxID tx_id) {
  std::shared_lock lock(active_transaction_mutex);
  auto it = active_transactions.find(tx_id);
  if (it == active_transactions.end()) {
    return TransactionState::COMMITTED; // Return committed or aborted, for now we assume committed
  }
  return TransactionState::ACTIVE;
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
  std::unique_lock lock(active_transaction_mutex);
  auto it = active_transactions.find(tx_id);
  if (it == active_transactions.end()) {
    std::string msg = "[COMMIT] Transaction " + std::to_string(tx_id) + " not found";
    throw std::runtime_error(msg);
  }
  Transaction& transaction = *(it->second);
  if (transaction.state != TransactionState::ACTIVE) {
    throw std::runtime_error("Transaction not active");
  }
  transaction.state = TransactionState::COMMITTED;
  lock_mgr.release_all_locks(transaction);
  catalog.commit_in_progress_tables(tx_id);
  active_transactions.erase(it);
}

void TransactionManager::abort_transaction(TxID tx_id) {
  std::unique_lock lock(active_transaction_mutex);
  auto it = active_transactions.find(tx_id);
  if (it == active_transactions.end()) {
    std::string msg = "[ABORT] Transaction " + std::to_string(tx_id) + " not found";
    throw std::runtime_error(msg);
  }
  Transaction& transaction = *(it->second);
  // Undo changes made by this transaction
  transaction.abort();
  lock_mgr.release_all_locks(transaction);
  catalog.abort_in_progress_tables(tx_id);
  transaction.set_state(TransactionState::COMMITTED);
  active_transactions.erase(it);
}

void TransactionManager::add_to_first_rids(TableId table_id, RID rid, TxID tx_id) {
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
