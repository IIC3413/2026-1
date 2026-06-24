#include "heap_file.h"

#include "exceptions/exceptions.h"
#include "storage/heap_file/heap_file_iter.h"
#include "storage/heap_file/heap_file_page.h"
#include "system/system.h"

HeapFile::HeapFile(const Schema& _schema, FileId file_id, TableId table_id)
    : schema(_schema),
      table_id(table_id),
      file_id(file_id) {
  for (auto& col : schema.columns) {
    col.table_id = table_id;
  }
  assert(!schema.columns.empty());
}

// write method gets the lock and calls update_record and insert_record_for_update
RID HeapFile::insert_record(const Record& record, TxID tx_id, std::optional<RID> first_rid) {
  RID res;
  // search block with available space and insert it there
  while (true) {
    int64_t page_num = last_insert_page;
    auto current_page = std::make_unique<HeapFilePage>(*this, last_insert_page);
    if (current_page->try_insert_record(record, &res, tx_id, first_rid)) {
      if (first_rid == std::nullopt) {
        // Regular inserts do not acquire a tuple lock through try_acquire_lock(),
        // so their RID is not automatically added to the transaction write set
        // We store it here so the inserted tuple can be rolled back on abort
        transaction_mgr.add_to_write_set(table_id, res, tx_id);
      }
      return res;
    }
    last_insert_page.compare_exchange_strong(page_num, page_num + 1); // making it thread safe
  }
}

RID HeapFile::get_last_version(const RID& rid) const {
  RID current_rid = rid;
  while (true) {
    HeapFilePage page(*this, current_rid.page_num);
    const auto record_header = page.get_record_header(current_rid.dir_slot);
    if (record_header.is_invalid()) { // deleted physically
      return RID(-1, -2);
    }
    uint64_t t_max = record_header.t_max;
    if (t_max == 0) {
      break;
    } else {
      RID next_rid = record_header.next;
      if (next_rid == RID(-1, -1)) {
        return current_rid; // last version before logical delete
      }
      current_rid = next_rid;
    }
  }
  return current_rid;
}

// update record managing versions and concurrency
RID HeapFile::update(RID rid, const Record& record, TxID tx_id) {
  if (transaction_mgr.get_isolation_level(tx_id) == IsolationLevel::READ_COMMITTED) {
    const auto record_header = get_record_header(rid);
    if (record_header.is_invalid()) {
      return RID(-1, -2); // record deleted physically
    }
    if (lock_mgr.try_acquire_lock(tx_id, table_id, record_header.first)) {
      // transaction_mgr.add_to_write_set(table_id, record_header.first, tx_id);
      RID to_update_rid = get_last_version(record_header.first);
      auto to_update_header = get_record_header(to_update_rid);
      if (to_update_header.is_invalid()) {
        return RID(-1, -2); // record deleted physically
      }
      if (to_update_header.next == RID(-1, -1)) {
        return RID(-1, -1); // record deleted logically
      }

      RID new_rid = insert_record(record, tx_id, record_header.first);
      HeapFilePage page(*this, to_update_rid.page_num);
      page.update_record_header(to_update_rid.dir_slot, new_rid, tx_id);
      return new_rid;
    }
  } else if (transaction_mgr.get_isolation_level(tx_id) == IsolationLevel::SNAPSHOT_ISOLATION) {
    const auto record_header = get_record_header(rid);
    if (record_header.is_invalid()) {
      return RID(-1, -2); // record deleted physically
    }
    if (lock_mgr.try_acquire_lock(tx_id, table_id, record_header.first)) {
       //TODO: Lab4 - Problem 4
    }
  }
  return RID(-1, -1);
}

std::unique_ptr<HeapFileIter> HeapFile::get_record_iter(TxID tx_id) const {
  return std::make_unique<HeapFileIter>(*this, tx_id);
}

void HeapFile::delete_record(RID rid, TxID tx_id) {
  if (transaction_mgr.get_isolation_level(tx_id) == IsolationLevel::READ_COMMITTED) {
    const TableId table_id = schema.columns.empty() ? 0 : schema.columns[0].table_id;
    const auto record_header = get_record_header(rid);
    if (record_header.is_invalid())
      return;
    if (lock_mgr.try_acquire_lock(tx_id, table_id, record_header.first)) {
      //TODO: Lab4 - Problem 3
    }
  } else if (transaction_mgr.get_isolation_level(tx_id) == IsolationLevel::SNAPSHOT_ISOLATION) {
    const TableId table_id = schema.columns.empty() ? 0 : schema.columns[0].table_id;
    const auto record_header = get_record_header(rid);
    if (record_header.is_invalid())
      return;
    if (lock_mgr.try_acquire_lock(tx_id, table_id, record_header.first)) {
      // transaction_mgr.add_to_write_set(table_id, record_header.first, tx_id);
      auto last_version = get_last_version(record_header.first);
      auto last_header = get_record_header(last_version);

      if (last_header.is_invalid()) {
        return; // record deleted physically
      }

      if (last_header.t_max == tx_id && last_header.next == RID(-1, -1)) {
        return; // record deleted logically by this tx
      }

      bool visible = is_visible(last_header, tx_id);

      if (!visible || (visible && last_header.next == RID(-1, -1))) {
        // mark transaction aborted and undo any modification
        transaction_mgr.abort_transaction(tx_id);
        throw TransactionAbortException(
            "Transaction " + std::to_string(tx_id) +
            " aborted due to a write-write conflict under Snapshot Isolation."
        );
        return;
      }

      HeapFilePage page(*this, last_version.page_num);
      page.delete_record_logically(last_version.dir_slot, tx_id);
    }
  }
}

// Undo when a transaction aborted
void HeapFile::undo(RID first_rid, TxID tx_id) {
  uint64_t t_max;
  uint64_t t_min;
  RID current_rid = first_rid;
  while (true) {
    if (current_rid == RID(-1, -1) || current_rid.dir_slot == -2)
      return;

    RecordHeader header = get_record_header(current_rid);
    if (header.is_invalid()) {
      return;
    }
    return; // You will need to remove this line in your solution
    //TODO: Lab4 - Problem 2
  }
}

void HeapFile::vacuum() {
  auto total_pages = file_mgr.count_pages(file_id);

  for (auto i = 0; i < total_pages; i++) {
    HeapFilePage page(*this, i);
    page.vacuum();
  }
  last_insert_page = 0;
}

void HeapFile::full_vacuum() {
  // Cleans dead tuples and updates the first RID to the last version.
  // doesn't admit concurrent transactions.
  const auto total_pages = file_mgr.count_pages(file_id);
  int64_t current_page_number = 0;
  std::unique_ptr<HeapFilePage> current_page = std::make_unique<HeapFilePage>(*this, 0);
  int64_t current_page_record_pos = -1;

  while (current_page != nullptr) {
    current_page_record_pos++;
    // static_cast in not necessary, only to avoid a warning
    if (current_page_record_pos >= static_cast<int64_t>(current_page->get_dir_count())) {
      current_page_record_pos = -1;
      current_page_number++;
      current_page->vacuum(); // once the page is clean we do vacuum

      if (current_page_number < total_pages) {
        current_page = std::make_unique<HeapFilePage>(*this, current_page_number);
        continue;
      } else {
        current_page = nullptr;
        break;
      }
    }
    auto current_record_header = current_page->get_record_header(current_page_record_pos);

    if (current_record_header.is_invalid()) { // only if delete is physical
      continue;
    }

    RID current_rid(current_page_number, current_page_record_pos);
    if (current_rid == current_record_header.first) {

      while (current_record_header.t_max != 0) {
        auto page = std::make_unique<HeapFilePage>(*this, current_rid.page_num);
        current_record_header = page->get_record_header(current_rid.dir_slot);

        if (current_rid == current_record_header.next) {
          page->reset_first(current_rid.dir_slot);
          break;
        } else {
          page->delete_record_physically(current_rid.dir_slot); // delete physically

          if (current_record_header.next == RID(-1, -1)) {
            break; // tuple logically deleted
          }
          current_rid = current_record_header.next;
        }
      }
    }
  }

  while (current_page_number >= 0) { // delete empty pages
    auto page = std::make_unique<HeapFilePage>(*this, current_page_number);
    if (page->is_page_empty()) {
      page.reset();
      buffer_mgr.delete_page(file_id, current_page_number);
      current_page_number--;
    } else {
      if (total_pages != current_page_number + 1) {
        file_mgr.truncate_file(file_id, current_page_number + 1);
      }
      break;
    }
  }

  last_insert_page = 0;
}

Record HeapFile::get_record(RID rid) const {
  HeapFilePage page(*this, rid.page_num);
  return page.get_record(rid.dir_slot);
}

RecordHeader HeapFile::get_record_header(RID rid) const {
  if (rid == RID(-1, -2)) {
    return RecordHeader();
  }
  HeapFilePage page(*this, rid.page_num);
  return page.get_record_header(rid.dir_slot);
}

RID HeapFile::read(RID rid, TxID tx_id, bool& valid) const {
  valid = false;
  RID current_rid = rid;
  uint64_t t_max = -1;
  while (t_max != 0) {
    auto record_header = get_record_header(current_rid);
    if (record_header.is_invalid()) {
      valid = false;
      return RID(-1, -2);
    }
    t_max = record_header.t_max;

    if (is_visible(record_header, tx_id)) {
      valid = true;
      return current_rid; // reached last version
    } else {
      current_rid = record_header.next;
      if (current_rid == RID(-1, -1)) {
        return current_rid; // tuple deleted
      }
    }
  }
  return current_rid;
}

bool HeapFile::is_visible(const RecordHeader& record_header, TxID tx_id) const {
  // TODO:
  // We are missing a snapshot of txs (Not for Read committed) see 5.6: Visibility Check Rules interdb.jp
  // assuming that commited transactions are removed from active_transactions
  // assuming that aborted transactions clean up their versions from the heap file
  uint64_t t_min = record_header.t_min;
  uint64_t t_max = record_header.t_max;

  auto [state_min, state_max] = transaction_mgr.get_states(t_min, t_max);

  // shouldn't be necessary
  // if (transaction_mgr.get_state(t_min) == TransactionState::ABORTED)
  //  return false;
  if (transaction_mgr.get_isolation_level(tx_id) == IsolationLevel::READ_COMMITTED) {
    if (state_min == TransactionState::ACTIVE) {
      if (t_min == tx_id) { // the transaction that created the record is the current transaction
        if (t_max == 0) {   // reach last version
          return true;
        } else {
          return false; // its not last version so not visible
        }
      } else {
        return false; // trying to see a record created by another active transaction
      }
    } else {
      if (t_max == 0) { // last version committed
        return true;
      }
      if (state_max == TransactionState::ACTIVE) {
        if (t_max == tx_id) {
          return false; // current transaction set t_max so not visible
        } else {
          return true; // another active transaction set t_max so visible
        }
      } else {
        return false; // t_max committed so not visible
      }
    }
  } else if (transaction_mgr.get_isolation_level(tx_id) == IsolationLevel::SNAPSHOT_ISOLATION) {
    //TODO: Lab4 - Problem 1
  }
  return false;
}