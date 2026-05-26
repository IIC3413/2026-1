#pragma once
#include "query/executor/hash_join/hash_table.h"
#include "query/executor/hash_join/hash_table_iter.h"
#include "query/optimizer/optimizer.h"
#include "query/parser/logical_plan/logical_plan.h"

#include <filesystem>
#include <fstream>
#include <iostream>

  // static constexpr auto CAPACITY = 4096;

bool files_are_equal(const std::filesystem::path& a, const std::filesystem::path& b) {
  std::ifstream file1(a, std::ios::binary);
  std::ifstream file2(b, std::ios::binary);

  if (!file1 || !file2) {
    return false;
  }

  return std::equal(
      std::istreambuf_iterator<char>(file1), std::istreambuf_iterator<char>(),
      std::istreambuf_iterator<char>(file2)
  );
}

void print_inter(HashTable& hash_table, std::vector<Value> keys, std::ostream& out) {
  int record_count = 0;
  for (auto& key : keys) {
    auto iter = hash_table.probe(key);
    iter->begin();
    auto record = iter->next();
    while (!record.invalid()) {
      out << record_count << ":(" << record.to_string() << ")\n";
      record = iter->next();
      ++record_count;
    }
  }
}

void process_query(std::unique_ptr<LogicalPlan> logical_plan, bool explain, TxID tx_id, std::ostream& out) {
  Optimizer optimizer(tx_id);
  auto physical_plan = optimizer.create_physical_plan(std::move(logical_plan));

  if (std::holds_alternative<std::unique_ptr<QueryAction>>(physical_plan)) {
    auto action = std::move(std::get<std::unique_ptr<QueryAction>>(physical_plan));
    action->execute();
  } else if (std::holds_alternative<std::unique_ptr<QueryIter>>(physical_plan)) {
    auto query_iter = std::move(std::get<std::unique_ptr<QueryIter>>(physical_plan));

    if (explain) {
      std::cout << "\n=== Physical Plan ===\n";
      query_iter->print_to_ostream(std::cout, 0);
      std::cout << std::endl;
    }

    query_iter->begin();
    Record record = query_iter->next();

    int record_count = 0;
    while (!record.invalid()) {
      out << record_count << ":(" << record.to_string() << ")\n";
      record = query_iter->next();
      ++record_count;
    }
  }
}