#pragma once

#include <set>

#include "storage/tuple_key.h"
#include "system/tx_id.h"

enum class IsolationLevel { READ_COMMITTED, SNAPSHOT_ISOLATION };

// aborted tx clean up their changes immediately, so anything on HeapFile is either active or committed
enum class TransactionState { ACTIVE, COMMITTED };

class Transaction {
  friend class TransactionManager;

public:
  Transaction(TxID id, IsolationLevel isolation_level);

  TxID get_id() const;

  IsolationLevel get_isolation_level() const;

  const std::set<TupleKey>& get_first_rids() const;

  TransactionState get_state() const;

  void set_state(TransactionState new_state);

  bool is_committed() const;

  void commit();

  bool abort() const;

private:
  TxID id;

  IsolationLevel isolation_level;

  // The transaction needs to save all records that were modified
  // When a record is modified only its first RID is saved
  std::set<TupleKey> first_rids;

  // tables created by this transaction, used for cleaning up after aborting
  std::set<TableId> created_tables;

  TransactionState state;
};
