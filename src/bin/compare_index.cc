#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "relational_model/value.h"
#include "storage/linear_hash_index/hash_index.h"
#include "storage/linear_hash_index/hash_index_bucket.h"
#include "storage/linear_hash_index/hash_index_dir.h"
#include "system/system.h"
#include "test_helpers.h"

using namespace std;

inline std::pair<std::vector<std::string>, bool>
capture_records_for_keys(HashIndex &idx, const std::vector<int> &keys) {
  std::vector<std::string> out;
  bool compacted = true;

  for (int k : keys) {
    auto index_iter = idx.get_iter(Value(k));
    index_iter->begin();

    // --- check compactation por cadena de buckets ---
    int32_t page = idx.hash_to_bucket_page(Value(k).get_hash(), idx.depth);

    while (page != -1) {
      BucketPage bp(idx, page);
      int32_t next = bp.get_overflow_pointer();

      if (next != -1 &&
          bp.get_tuple_count() != BucketPage::MAX_VALUES_PER_BUCKET) {
        compacted = false;
      }

      page = next;
    }

    // --- capturar records ---
    auto record = index_iter->next();
    while (!record.invalid()) {
      out.push_back(record.to_string());
      record = index_iter->next();
    }
  }

  return {out, compacted};
}

static vector<vector<string>> build_page_snapshot(HashIndex &hash_index) {
  vector<vector<string>> pages;

  size_t split_buckets_count = static_cast<size_t>(
      std::round(hash_index.N * std::pow(2, hash_index.depth)));
  size_t bucket_count = split_buckets_count + hash_index.split_pointer;

  for (size_t b = 0; b < bucket_count; ++b) {
    auto page_num = hash_index.dir.get_bucket_page(b);
    int32_t current = static_cast<int32_t>(page_num);
    while (current != -1) {
      BucketPage bp(hash_index, current);
      int64_t tuple_count = bp.get_tuple_count();
      vector<string> page_lines;
      for (int64_t i = 0; i < tuple_count; ++i) {
        HashIndexRecord rec = bp.get_record(i);
        auto record = hash_index.heap_file.get_record(rec.rid);
        page_lines.push_back(record.to_string());
      }
      pages.push_back(std::move(page_lines));
      current = static_cast<int32_t>(bp.get_overflow_pointer());
    }
  }
  return pages;
}

bool compare_garbage_collector(HashIndex &ref_idx, HashIndex &stu_idx) {
  auto ref_page = ref_idx.dir.get_page_collector_pointer();
  auto stu_page = stu_idx.dir.get_page_collector_pointer();
  while (ref_page == stu_page) {
    if (ref_page == -1) {
      return true;
    }
    ref_page = BucketPage(ref_idx, ref_page).get_overflow_pointer();
    stu_page = BucketPage(stu_idx, stu_page).get_overflow_pointer();
  }
  return false;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "Usage: compare_index <table>  (will compare <table>.ref "
                 "against <table>)"
              << std::endl;
    return EXIT_FAILURE;
  }

  // Program requires a single table name; reference table is <table>.ref
  string table = argv[1];

  string mode = "multiset";
  vector<int> keys;
  string dump_path;
  double score = 0.75;

  int i = 2; // parse optional flags after the table name
  while (i < argc) {
    string a = argv[i];
    if (a == "--mode") {
      if (i + 1 >= argc) {
        std::cerr << "--mode requires an argument\n";
        return EXIT_FAILURE;
      }
      mode = argv[++i];
      i++;
    } else if (a == "--keys") {
      if (i + 1 >= argc) {
        std::cerr << "--keys requires an argument\n";
        return EXIT_FAILURE;
      }
      string csv = argv[++i];
      string token;
      stringstream ss(csv);
      while (getline(ss, token, ',')) {
        try {
          keys.push_back(stoi(token));
        } catch (...) {
        }
      }
      i++;
    } else if (a == "--dump-student-snapshot") {
      if (i + 1 >= argc) {
        std::cerr << "--dump-student-snapshot requires an argument\n";
        return EXIT_FAILURE;
      }
      dump_path = argv[++i];
      i++;
    } else if (a == "--score") {
      if (i + 1 >= argc) {
        std::cerr << "--score requires an argument\n";
        return EXIT_FAILURE;
      }
      score = std::stod(argv[++i]);
      i++;
    } else {
      std::cerr << "Unknown option: " << a << std::endl;
      return EXIT_FAILURE;
    }
  }

  filesystem::path dirPath = "data/example_db";
  auto system = System(dirPath);

  auto info = catalog.get_table_info(table);

  if (info == nullptr) {
    std::cerr << "Reference table not found: " << table << std::endl;
    return EXIT_FAILURE;
  }

  FileId ref_dir = file_mgr.get_file_id(info->name + ".ref.dir");
  FileId ref_buckets = file_mgr.get_file_id(info->name + ".ref.hidx");

  FileId stu_dir = file_mgr.get_file_id(info->name + ".dir");
  FileId stu_buckets = file_mgr.get_file_id(info->name + ".hidx");

  auto &heap = info->heap_file;

  int key_col_idx = 1;
  HashIndex ref_idx(*heap, key_col_idx, ref_dir, ref_buckets);
  HashIndex stu_idx(*heap, key_col_idx, stu_dir, stu_buckets);

  if (ref_idx.depth != stu_idx.depth ||
      ref_idx.split_pointer != stu_idx.split_pointer) {
    std::cout << "MISMATCH (multiset)\n" << 0.0 << std::endl;
    return EXIT_SUCCESS;
  }

  if (mode == "multiset") {

    // 1. Garbage collector
    if (!compare_garbage_collector(ref_idx, stu_idx)) {
      std::cout << "MISMATCH (multiset)\n" << 0.0 << std::endl;
      return EXIT_SUCCESS;
    }

    // 2. Captura + compactación
    auto [ref_snap, ref_compacted] = capture_records_for_keys(ref_idx, keys);
    auto [stu_snap, stu_compacted] = capture_records_for_keys(stu_idx, keys);

    if (!stu_compacted) {
      std::cout << "MISMATCH (multiset)\n" << 0.0 << std::endl;
      return EXIT_SUCCESS;
    }

    // 3. Comparación de contenido
    sort_snapshot(ref_snap);
    sort_snapshot(stu_snap);

    if (!compare_sorted_snapshots(ref_snap, stu_snap)) {
      std::cout << "MISMATCH (multiset)\n" << 0.0 << std::endl;
      return EXIT_SUCCESS;
    }

    // Dump opcional (solo si todo pasó)
    if (!dump_path.empty()) {
      save_snapshot(dump_path, stu_snap);
    }

    // Todo OK
    std::cout << "MATCH (multiset)\n" << score << std::endl;
    return EXIT_SUCCESS;
  } else if (mode == "page") {
    auto ref_pages = build_page_snapshot(ref_idx);
    auto stu_pages = build_page_snapshot(stu_idx);

    bool ok = true;
    if (ref_pages.size() != stu_pages.size()) {
      ok = false;
    } else {
      for (size_t p = 0; p < ref_pages.size() && ok; ++p) {
        const auto &a = ref_pages[p];
        const auto &b = stu_pages[p];
        if (a.size() != b.size()) {
          ok = false;
          break;
        }
        for (size_t s = 0; s < a.size(); ++s) {
          if (a[s] != b[s]) {
            ok = false;
            break;
          }
        }
      }
    }

    if (!dump_path.empty()) {
      std::ofstream ofs(dump_path);
      for (size_t p = 0; p < stu_pages.size(); ++p) {
        ofs << "#PAGE " << p << "\n";
        for (const auto &line : stu_pages[p])
          ofs << line << "\n";
      }
    }

    if (ok) {
      std::cout << "MATCH (page)\n" << score << std::endl;
      return EXIT_SUCCESS;
    } else {
      std::cout << "MISMATCH (page)\n" << 0.0 << std::endl;
      return EXIT_SUCCESS;
    }
  } else {
    std::cerr << "Unknown mode: " << mode << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
