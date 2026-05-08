// Test helper utilities for snapshots and order-insensitive comparison
#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "storage/linear_hash_index/hash_index.h"

inline void sort_snapshot(std::vector<std::string>& s) {
  std::sort(s.begin(), s.end());
}

inline bool compare_sorted_snapshots(const std::vector<std::string>& a, const std::vector<std::string>& b) {
  if (a.size() != b.size()) return false;
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i] != b[i]) return false;
  }
  return true;
}

inline void save_snapshot(const std::string& path, std::vector<std::string> snapshot) {
  std::sort(snapshot.begin(), snapshot.end());
  std::ofstream ofs(path);
  for (auto &s : snapshot) ofs << s << "\n";
}
