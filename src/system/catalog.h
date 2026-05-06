#pragma once

#include <atomic>
#include <fstream>
#include <map>
#include <shared_mutex>
#include <string>
#include <sys/types.h>
#include <vector>

#include "relational_model/record.h"
#include "relational_model/schema.h"
#include "relational_model/table_info.h"
#include "storage/file_id.h"
#include "storage/rid.h"
#include "system/tx_id.h"

class Catalog {
public:
  Catalog(const std::string& filename);

  ~Catalog();

  const TableInfo* create_table(const std::string& table_name, const Schema&, TxID tx_id);

  RID insert_record(const std::string& table_name, const Record& record, TxID tx_id);

  RID update_record(const std::string& table_name, RID rid, const Record& record, TxID tx_id);

  // Doesn't support concurrency
  void vacuum(TxID tx_id);

  void delete_record(const std::string& table_name, RID rid, TxID tx_id);

  const TableInfo* get_table_info(const std::string& table_name, TxID tx_id);

  const TableInfo* get_table_info(TableId table_id, TxID tx_id);

  bool table_exists(const std::string& table_name, TxID tx_id) {
    return get_table_info(table_name, tx_id) != nullptr;
  }

  uint64_t update_transaction_count() {
    return transaction_count.fetch_add(1);
  }

  void commit_in_progress_tables(TxID tx_id);

  void abort_in_progress_tables(TxID tx_id);

  void create_index(const std::string& table_name, const std::string& column_name, TxID tx);

  const std::unique_ptr<Index>& get_index(const std::string& table_name, IndexId index_id, TxID tx);

private:
  std::shared_mutex tables_mutex;

  std::atomic<uint64_t> table_id_counter = 0;

  std::atomic<uint64_t> transaction_count = 0;

  // Tables created for not committed transactions
  std::map<TxID, std::vector<std::unique_ptr<TableInfo>>> in_process_tables;

  // Commited tables
  std::map<TableId, std::unique_ptr<TableInfo>> table_id2table_info;

  std::fstream file;

  static std::string normalize(const std::string& table_name);

  int64_t read_int64();

  std::string read_string();

  void write_int64(const int64_t);

  void write_string(const std::string&);

  FileId get_file_id(const std::string& table_name, TableId table_id);
};
