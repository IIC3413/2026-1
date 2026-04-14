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
This test checks the correctness of the vacuum operation for case 2:
2) Deleting the last two records (tail slots) and vacuuming should cause the dir_count to shrink by 2, effectively removing the deleted slots from the page.
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

	// Case 2: delete trailing slots (dir_count-2 and dir_count-1) and expect dir_count shrink.
	HeapFilePage page_before_case2(*table, 0);
	const int32_t dir_count_before_case2 = page_before_case2.get_dir_count();
	const int32_t tail_a = dir_count_before_case2 - 2;
	const int32_t tail_b = dir_count_before_case2 - 1;

	bool case2_ok = true;
	if (tail_a < 0 || tail_b < 0 || !is_live_slot(page_before_case2, tail_a) || !is_live_slot(page_before_case2, tail_b)) {
		case2_ok = false;
	} else {
		table->delete_record(RID(0, tail_a), 0);
		table->delete_record(RID(0, tail_b), 0);
		table->vacuum();

		HeapFilePage page_after_case2(*table, 0);

		const int32_t dir_count_after_case2 = page_after_case2.get_dir_count();

		const bool dir_count_shrunk = (dir_count_after_case2 == dir_count_before_case2 - 2);

		case2_ok = dir_count_shrunk;
	}

	if (case2_ok) {
		score += 0.5;
	}

	std::cout << std::fixed << std::setprecision(1) << score << std::endl;

	return (score == 0.5) ? EXIT_SUCCESS : EXIT_FAILURE;
}
