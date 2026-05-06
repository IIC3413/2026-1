#include "hash_join.h"

HashJoin::HashJoin(
    std::unique_ptr<QueryIter> _lhs,
    std::unique_ptr<QueryIter> _rhs,
    std::vector<ProjectedColumn>&& _projected_lhs_columns,
    std::vector<ProjectedColumn>&& _projected_rhs_columns,
    std::pair<size_t, size_t>&& _equality
)
    : lhs(std::move(_lhs)),
      rhs(std::move(_rhs)),
      projected_lhs_columns(std::move(_projected_lhs_columns)),
      projected_rhs_columns(std::move(_projected_rhs_columns)),
      equality(std::move(_equality)) {}

void HashJoin::begin() {
  lhs->begin();
  rhs->begin();

  prepare();
}

void HashJoin::prepare() {
  std::vector<DataType> datatypes;
  for (auto& pjc : projected_lhs_columns) {
    datatypes.push_back(pjc.col.info.datatype);
  }

  htbl = std::make_unique<HashTable>(equality.first, datatypes);
  state = State::BUILD;
}

// simple nested loop join
Record HashJoin::next() {
  // TODO: Problema 3
  return Record();
}

void HashJoin::reset() {
  lhs->reset();
  rhs->reset();
  prepare();
}

std::vector<Column> HashJoin::get_columns() {
  std::vector<Column> res;
  for (auto& c : projected_lhs_columns) {
    res.push_back(c.col);
  }
  for (auto& c : projected_rhs_columns) {
    res.push_back(c.col);
  }
  return res;
}

std::ostream& HashJoin::print_to_ostream(std::ostream& os, int indent) const {
  os << std::string(indent, ' ');
  os << "HashJoin(";
  os << projected_lhs_columns[equality.first].col.alias << "."
     << projected_lhs_columns[equality.first].col.info.name;
  os << " == ";
  os << projected_rhs_columns[equality.second].col.alias << "."
     << projected_rhs_columns[equality.second].col.info.name;
  os << ")\n";
  lhs->print_to_ostream(os, indent + 2);
  rhs->print_to_ostream(os, indent + 2);
  return os;
}
