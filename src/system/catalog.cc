#include "catalog.h"

#include <algorithm>
#include <stdexcept>
#include <iostream>

#include "exceptions/exceptions.h"
#include "relational_model/schema.h"
#include "storage/heap_file/heap_file.h"
#include "system/system.h"
#include "storage/linear_hash_index/hash_index.h"

using namespace std;

std::string Catalog::normalize(const std::string& table_name) {
  std::string res = table_name;
  std::transform(res.begin(), res.end(), res.begin(), [](unsigned char c) { return std::tolower(c); });

  for (char c : res) {
    if ((c < 'a' || c > 'z') && c != '_') {
      throw QueryException(
          "wrong table name: `" + table_name + "`. Only a-z letters and underscore ('_') are allowed."
      );
    }
  }
  return res;
}

Catalog::Catalog(const string& filename) {
  auto file_path = file_mgr.get_file_path(filename);
  file.open(file_path, ios::out | ios::app);
  if (file.fail()) {
    throw std::runtime_error("Could not open file " + filename);
  }
  file.close();
  file.open(file_path, ios::in | ios::out | ios::binary);

  file.seekg(0, file.end);
  if (file.tellg() == 0) {
    return; // catalog file is new
  }

  file.seekg(0, file.beg);

  transaction_count.store(read_int64());
  table_id_counter = read_int64();
  int64_t tables_count = read_int64();
  for (int64_t i = 0; i < tables_count; ++i) {
    std::string table_name = read_string();
    int64_t table_cardinality = read_int64();
    TableId table_id = read_int64();
    int64_t table_column_count = read_int64();
    std::vector<ColumnInfo> columns;

    for (int64_t c = 0; c < table_column_count; ++c) {
      DataType d = static_cast<DataType>(read_int64());
      std::string col_name = read_string();
      columns.push_back({col_name, d, table_id});
    }

    auto schema = std::make_unique<Schema>(std::move(columns));

    auto& schema_ref = *schema.get();
    auto table_file_id = get_file_id(table_name, table_id);
    auto heap_file = std::make_unique<HeapFile>(schema_ref, table_file_id, table_id);

    std::vector<std::unique_ptr<Index>> index;
    int64_t index_counter = read_int64();

    for (int64_t j = 0; j < index_counter; ++j) {
      IndexType index_type = static_cast<IndexType>(read_int64());
      // IndexId index_id = read_int64();
      switch (index_type) {
      case IndexType::LINEAR_HASH_INDEX: {

        auto key_col_idx = read_int64();
        FileId dir_file_id = file_mgr.get_file_id(normalize(table_name) + "." + std::to_string(j) + ".dir");
        FileId buckets_file_id = file_mgr.get_file_id(normalize(table_name) + "." + std::to_string(j)+ ".hidx");

        index.push_back(std::make_unique<HashIndex>(*heap_file, key_col_idx, dir_file_id, buckets_file_id));
        break;
      }
      case IndexType::B_PLUS_TREE:
        break;
      case IndexType::NONE:
        break;
      }
    }

    table_id2table_info.insert(
        {table_id, std::make_unique<TableInfo>(
                       table_name, std::move(schema), std::move(heap_file), table_id, table_cardinality, std::move(index)
                   )}
    );
  }
}

Catalog::~Catalog() {
  file.seekg(0, file.beg);
  write_int64(transaction_count.load());
  write_int64(table_id_counter);
  write_int64(table_id2table_info.size());
  for (auto& [table_id, table_info] : table_id2table_info) {
    write_string(table_info->name);
    auto& schema = table_info->schema;

    write_int64(table_info->cardinality);
    write_int64(table_info->table_id);
    write_int64(schema->columns.size());
    for (size_t i = 0; i < schema->columns.size(); i++) {
      write_int64(static_cast<int64_t>(schema->columns[i].datatype));
      write_string(schema->columns[i].name);
    }
    // write indexes
    write_int64(table_info->indexes.size());
    if (!table_info->indexes.empty()) {
      for (auto& index : table_info->indexes) {
        auto index_type = index->get_type();
        write_int64(static_cast<uint64_t>(index_type));

        switch (index_type) {
        case IndexType::LINEAR_HASH_INDEX: {
          auto casted = reinterpret_cast<HashIndex*>(index.get());
          write_int64(casted->key_column_idx);
          break;
        }
        case IndexType::B_PLUS_TREE:
          break;
        case IndexType::NONE:
          break;
        }
      }
    }
  }

  file.close();
}

int64_t Catalog::read_int64() {
  int64_t res = 0;
  uint8_t buf[8];
  file.read((char*)buf, sizeof(buf));

  for (int i = 0, shift = 0; i < 8; ++i, shift += 8) {
    res |= static_cast<int64_t>(buf[i]) << shift;
  }

  if (!file.good()) {
    throw std::runtime_error("Error reading int64");
  }

  return res;
}

string Catalog::read_string() {
  auto len = read_int64();
  char* buf = new char[len];
  file.read(buf, len);
  string res(buf, len);
  delete[] buf;
  return res;
}

void Catalog::write_int64(const int64_t n) {
  uint8_t buf[8];
  for (unsigned int i = 0, shift = 0; i < sizeof(buf); ++i, shift += 8) {
    buf[i] = (n >> shift) & 0xFF;
  }
  file.write(reinterpret_cast<const char*>(buf), sizeof(buf));
}

void Catalog::write_string(const string& s) {
  write_int64(s.size());
  file.write(s.c_str(), s.size());
}

const TableInfo*
Catalog::create_table(const std::string& table_name, const Schema& schema, TxID tx_id) {
  std::string normalized_table_name = normalize(table_name);

  auto table_exists = get_table_info(normalized_table_name, tx_id);
  if (table_exists != nullptr) {
    throw QueryException("Table `" + table_name + "` already exists.");
  }

  TableId table_id = table_id_counter.fetch_add(1);

  Schema final_schema = schema; // we need a schema with an additional RID column

  assert(final_schema.columns[final_schema.columns.size() - 1].datatype != DataType::RID);
  final_schema.columns.push_back({"RID", DataType::RID, table_id}); // implicit RID column
  for (auto& col : final_schema.columns) {
    col.table_id = table_id;
  }

  std::unique_lock lock(tables_mutex);

  auto file_id = get_file_id(normalized_table_name, table_id);
  auto heap_file = std::make_unique<HeapFile>(final_schema, file_id, table_id);

  auto table_info = std::make_unique<TableInfo>(
      normalized_table_name, std::make_unique<Schema>(final_schema), std::move(heap_file), table_id, 0
  );

  in_process_tables[tx_id].push_back(std::move(table_info));
  return in_process_tables[tx_id].back().get();
}

RID Catalog::insert_record(const std::string& table_name, const Record& record, TxID tx_id) {
  auto table_info = get_table_info(table_name, tx_id);
  if (table_info == nullptr) {
    throw QueryException("Table `" + table_name + "` does not exist.");
  }
  RID rid = table_info->heap_file->insert_record(record, tx_id);

  if (!table_info->indexes.empty()) {
    for (auto& index : table_info->indexes) {
      index->insert_record(rid);
    }
  }
  return rid;
}

void Catalog::delete_record(const std::string& table_name, RID rid, TxID tx_id) {
  auto table_info = get_table_info(table_name, tx_id);
  if (table_info == nullptr) {
    throw QueryException("Table `" + table_name + "` does not exist.");
  }

  if (!table_info->indexes.empty()) {
    for (auto& index : table_info->indexes) {
      index->delete_record(rid);
    }
  }
  // MUST delete from the index before the table, otherwise rid will be invalid
  table_info->heap_file->delete_record(rid);

}

RID Catalog::update_record(
    const std::string& table_name, RID rid, const Record& record, TxID tx_id
) {
  auto table_info = get_table_info(table_name, tx_id);

  if (table_info == nullptr) {
    throw QueryException("Table `" + table_name + "` does not exist.");
  }

  HeapFile* heap_file = table_info->heap_file.get();

  return heap_file->update(rid, record, tx_id);
}

void Catalog::vacuum(TxID tx_id) {
  std::vector<TableId> table_ids_to_vacuum;
  {
    std::shared_lock lock(tables_mutex);
    for (const auto& [table_id, table_info] : table_id2table_info) {
      table_ids_to_vacuum.push_back(table_id);
    }
  }

  for (TableId table_id : table_ids_to_vacuum) {
    auto table_info = get_table_info(table_id, tx_id);
    if (table_info != nullptr) {
      table_info->heap_file->vacuum();
    }
  }
}

const TableInfo* Catalog::get_table_info(const std::string& table_name, TxID tx_id) {
  std::string normalized_table_name = normalize(table_name);
  std::shared_lock lock(tables_mutex);

  for (const auto& [table_id, table_info] : table_id2table_info) {
    if (table_info->name == normalized_table_name) {
      return table_info.get();
    }
  };

  for (const auto& [other_tx_id, table_info_vec] : in_process_tables) {
    for (const auto& table_info : table_info_vec) {
      if (table_info->name == normalized_table_name && tx_id == other_tx_id) {
        return table_info.get();
      }
    }
  }
  return nullptr;
}

const TableInfo* Catalog::get_table_info(TableId table_id, TxID tx_id) {
  std::shared_lock lock(tables_mutex);
  auto it = table_id2table_info.find(table_id);
  if (it != table_id2table_info.end()) {
    return it->second.get();
  }

  for (const auto& [other_tx_id, table_info_vec] : in_process_tables) {
    for (const auto& table_info : table_info_vec) {
      if (table_info->table_id == table_id && tx_id == other_tx_id) {
        return table_info.get();
      }
    }
  }
  return nullptr;
}

// called when a transaction that created tables commits
void Catalog::commit_in_progress_tables(TxID tx_id) {
  std::unique_lock lock(tables_mutex);
  auto it = in_process_tables.find(tx_id);
  if (it == in_process_tables.end()) {
    return;
  }
  for (auto& table_info : it->second) {
    // Manage if table name already exists
    for (auto& [_, committed_table_info] : table_id2table_info) {
      if (table_info->name == committed_table_info->name) {
        transaction_mgr.abort_transaction(tx_id);
        throw QueryException(
            "Cannot commit transaction " + to_string(tx_id) + " because it creates a table with name `" +
            table_info->name + "` that already exists."
        );
      }
    }

    table_id2table_info.insert({table_info->table_id, std::move(table_info)});
  }
  in_process_tables.erase(it);
}

void Catalog::abort_in_progress_tables(TxID tx_id) {
  std::unique_lock lock(tables_mutex);
  auto it = in_process_tables.find(tx_id);
  if (it != in_process_tables.end()) {
    for (auto& table_info : it->second) {
      buffer_mgr.delete_file(table_info->heap_file->file_id);
      for (auto& index : table_info->indexes) {
        if (index->get_type() == IndexType::LINEAR_HASH_INDEX){
          auto casted = static_cast<HashIndex*>(index.get());
          buffer_mgr.delete_file(casted->buckets_file_id);
          buffer_mgr.delete_file(casted->dir_file_id);
        }
      }
    }
    in_process_tables.erase(it);
  }
}

FileId Catalog::get_file_id(const std::string& table_name, TableId table_id) {
  std::string filename = to_string(table_id) + "_" + table_name + ".tbl";
  return file_mgr.get_file_id(filename);
}

void Catalog::create_index(const std::string& table_name, const std::string& column_name, TxID tx) {
  int key_col_idx;
  auto columns = get_table_info(table_name, tx)->schema->columns;
  for (size_t c = 0; c < columns.size(); ++c) {
    if (columns[c].name == column_name) key_col_idx = c;
  }

  TableInfo* table_info;
  for (const auto& [table_id, tinfo] : table_id2table_info) {
    if (tinfo->name == table_name) {
      table_info = tinfo.get();
    }
  };

  for (const auto& [other_tx_id, table_info_vec] : in_process_tables) {
    for (const auto& tinfo : table_info_vec) {
      if (tinfo->name == table_name && tx == other_tx_id) {
        table_info = tinfo.get();
      }
    }
  }

  auto index_count = table_info->indexes.size();
  FileId dir_file_id = file_mgr.get_file_id(normalize(table_name) + "." + std::to_string(index_count) + ".dir");
  FileId buckets_file_id = file_mgr.get_file_id(normalize(table_info->name) + "." + std::to_string(index_count) + ".hidx");

  table_info->indexes.push_back(std::make_unique<HashIndex>(*table_info->heap_file, key_col_idx, dir_file_id, buckets_file_id));

  auto iter = table_info->heap_file->get_record_iter(tx);
  iter->begin();
  while (!iter->next().invalid()) {
    table_info->indexes[index_count]->insert_record(iter->get_current_RID());
  }
}

const std::unique_ptr<Index>& Catalog::get_index(const std::string& table_name, IndexId index_id, TxID tx) {
  auto table_info = get_table_info(table_name, tx);
  assert(index_id < table_info->indexes.size());
  return table_info->indexes[index_id];
}
