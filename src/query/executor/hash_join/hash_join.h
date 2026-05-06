#pragma once

#include "hash_table.h"
#include "hash_table_iter.h"
#include "query/executor/query_iter.h"

#include <cassert>
#include <iostream>
#include <memory>

class HashJoin : public QueryIter {
public:
  HashJoin(
      std::unique_ptr<QueryIter> _lhs,
      std::unique_ptr<QueryIter> _rhs,
      std::vector<ProjectedColumn>&& _projected_lhs_columns,
      std::vector<ProjectedColumn>&& _projected_rhs_columns,
      std::pair<size_t, size_t>&& _equality
  );

  void begin() override;

  void prepare();

  // simple nested loop join
  Record next() override;

  void reset() override;

  std::vector<Column> get_columns() override;

  std::ostream& print_to_ostream(std::ostream& os, int indent = 0) const override;

private:
  enum class State { DONE, BUILD, PROBE };

  State state = State::DONE;
  std::unique_ptr<QueryIter> lhs;
  std::unique_ptr<QueryIter> rhs;
  std::vector<ProjectedColumn> projected_lhs_columns;
  std::vector<ProjectedColumn> projected_rhs_columns;
  std::pair<size_t, size_t> equality;
  Record current_lhs;
  Record current_rhs;
  std::unique_ptr<HashTable> htbl;
  std::unique_ptr<HashTableIter> hash_lhs;
  Record unprocessed_record;
};
