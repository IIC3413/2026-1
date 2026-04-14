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
This test checks the correctness of the vacuum operation for case 1:
1) Deleting two middle records (following dir slots order) and vacuuming should mark their dir slots as -1 and keep them in place.
*/


static bool is_live_slot(const HeapFilePage& page, int32_t dir_slot) {
	if (dir_slot < 0 || dir_slot >= page.get_dir_count()) {
		return false;
	}
	if (page.get_dir(dir_slot) <= 0) {
		return false;
	}
	return !page.get_record_header(dir_slot).is_invalid();
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
		std::cout << "Score: 0/0.5" << std::endl;
		return EXIT_FAILURE;
	}

	const std::vector<RID> case1_deleted = {RID(0, mid_a), RID(0, mid_b)};

	// Case 1: delete two middle records and expect their dir slots to remain as -2 after vacuum.
	table->delete_record(case1_deleted[0], 0);
	table->delete_record(case1_deleted[1], 0);
	table->vacuum();

	HeapFilePage page_after_case1(*table, 0);
	bool case1_ok = true;
	if (mid_b >= page_after_case1.get_dir_count()) {
		case1_ok = false;
	} else {
		case1_ok =
				(page_after_case1.get_dir(mid_a) == -2) &&
				(page_after_case1.get_dir(mid_b) == -2);
	}

	if (case1_ok) {
		score += 0.5;
	}

	std::cout << std::fixed << std::setprecision(1) << score << std::endl;

	return (score == 0.5) ? EXIT_SUCCESS : EXIT_FAILURE;
}
