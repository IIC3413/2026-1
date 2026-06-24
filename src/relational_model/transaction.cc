#include "transaction.h"

#include "storage/heap_file/heap_file.h"
#include "system/system.h"

Transaction::Transaction(uint64_t id, IsolationLevel isolation_level)
    : id(id),
      isolation_level(isolation_level) {}

uint64_t Transaction::get_id() const {
  return id;
}

IsolationLevel Transaction::get_isolation_level() const {
  return isolation_level;
}

const std::set<TupleKey>& Transaction::get_first_rids() const {
  return first_rids;
}

TransactionState Transaction::get_state() const {
  return state;
}

void Transaction::set_state(TransactionState new_state) {
  state = new_state;
}

bool Transaction::is_committed() const {
  return state == TransactionState::COMMITTED;
}

void Transaction::commit() {
  transaction_mgr.commit_transaction(id);
}

bool Transaction::abort() const {
  // needs to call every table updated by this transaction to undo
  for (const TupleKey& key : first_rids) {
    auto heap_file = catalog.get_table_info(key.table_id, this->id)->heap_file.get();
    heap_file->undo(key.first_rid, this->id);
  }
  return false;
}
