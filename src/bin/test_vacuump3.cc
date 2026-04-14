#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>

#include "relational_model/record.h"
#include "storage/heap_file/heap_file.h"
#include "storage/heap_file/heap_file_page.h"
#include "storage/rid.h"
#include "system/catalog.h"
#include "system/system.h"

/*
This test checks the correctness of the vacuum operation for RID stability:
3) After deleting middle slots and vacuuming, the records that were not deleted should remain unchanged and accessible by their RID (RID stability).
*/

static bool contains_rid(const std::vector<RID>& rids, const RID& rid) {
	for (const auto& r : rids) {
		if (r == rid) {
			return true;
		}
	}
	return false;
}

static bool is_live_slot(const HeapFilePage& page, int32_t dir_slot) {
	if (dir_slot < 0 || dir_slot >= page.get_dir_count()) {
		return false;
	}
	if (page.get_dir(dir_slot) <= 0) {
		return false;
	}
	return !page.get_record_header(dir_slot).is_invalid();
}

static std::map<RID, Record> snapshot_live_records(const HeapFile& heap_file, const std::vector<RID>& excluded) {
	std::map<RID, Record> snapshot;
	const int64_t total_pages = file_mgr.count_pages(heap_file.file_id);

	for (int64_t page_num = 0; page_num < total_pages; ++page_num) {
		HeapFilePage page(heap_file, page_num);
		const int32_t dir_count = page.get_dir_count();

		for (int32_t dir_slot = 0; dir_slot < dir_count; ++dir_slot) {
			if (!is_live_slot(page, dir_slot)) {
				continue;
			}
			const RID rid(page_num, dir_slot);
			if (contains_rid(excluded, rid)) {
				continue;
			}
			snapshot[rid] = page.get_record(dir_slot);
		}
	}

	return snapshot;
}

static bool validate_snapshot_after_vacuum(const HeapFile& heap_file, const std::map<RID, Record>& expected) {
	for (const auto& [rid, expected_record] : expected) {
		HeapFilePage page(heap_file, rid.page_num);
		if (!is_live_slot(page, rid.dir_slot)) {
			std::cout << "RID(" << rid.page_num << "," << rid.dir_slot << ") is not live after vacuum." << std::endl;
			return false;
		}

		const Record current = page.get_record(rid.dir_slot);
		if (!(current == expected_record)) {
			std::cout << "RID(" << rid.page_num << "," << rid.dir_slot << ") record content changed after vacuum."
								<< std::endl;
			return false;
		}
	}

	return true;
}

int main() {
	double score = 0.0;

	System system("data/example_db");
	const TableInfo* table_info = catalog.get_table_info("valid_table");
	if (table_info == nullptr) {
		std::cout << "Error: table valid_table does not exist." << std::endl;
		std::cout << "Score: 0/0.5" << std::endl;
		return EXIT_FAILURE;
	}

	HeapFile* table = table_info->heap_file.get();
	HeapFilePage page_before(*table, 0);
	const int32_t initial_dir_count = page_before.get_dir_count();

	if (initial_dir_count < 4) {
		std::cout << "Error: not enough dir slots to run this test." << std::endl;
		std::cout << "Score: 0/0.5" << std::endl;
		return EXIT_FAILURE;
	}

	int32_t mid_a = -1;
	int32_t mid_b = -1;
	for (int32_t i = 1; i + 2 < initial_dir_count; ++i) {
		if (is_live_slot(page_before, i - 1) &&
				is_live_slot(page_before, i) &&
				is_live_slot(page_before, i + 1) &&
				is_live_slot(page_before, i + 2)) {
			mid_a = i;
			mid_b = i + 1;
			break;
		}
	}

	if (mid_a == -1) {
		std::cout << "Error: could not find two middle live slots between non-deleted neighbors." << std::endl;
		std::cout << "Score: 0/1" << std::endl;
		return EXIT_FAILURE;
	}

	const std::vector<RID> case1_deleted = {RID(0, mid_a), RID(0, mid_b)};
	const auto snapshot_case1 = snapshot_live_records(*table, case1_deleted);

	// Case 1: delete two middle records and check RID stability.
	bool rid_stability_ok = true;
	table->delete_record(case1_deleted[0], 0);
	table->delete_record(case1_deleted[1], 0);
	table->vacuum();

	rid_stability_ok = validate_snapshot_after_vacuum(*table, snapshot_case1);

	if (rid_stability_ok) {
		score += 0.5;
	}

	std::cout << std::fixed << std::setprecision(1) << score << std::endl;

	return (score == 0.5) ? EXIT_SUCCESS : EXIT_FAILURE;
}
