#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "relational_model/record.h"
#include "relational_model/value.h"
#include "storage/heap_file/heap_file.h"
#include "storage/heap_file/heap_file_page.h"
#include "storage/rid.h"
#include "system/catalog.h"
#include "system/system.h"

namespace fs = std::filesystem;
/*
This test checks the correctness of the update operation as follows:
1) It performs a series of updates on two root records, creating chains of updated versions.
2) It verifies that all versions in the chain (including the last updated version) have the correct first_rid link pointing to the original root record.
*/



static Record build_updated_record(const Record& original) {
	std::vector<Value> values;
	values.reserve(original.values.size());

	for (const auto& v : original.values) {
		if (v.is_int()) {
			values.push_back(Value(v.as_int() + 1000));
		} else if (v.is_string()) {
			values.push_back(Value(v.as_string() + "_upd"));
		}
	}

	return Record(values);
}

int main() {
	const fs::path source_db("data/example_db");

	if (!fs::exists(source_db) || !fs::is_directory(source_db)) {
		std::cout << "Error: source database not found: " << source_db.string() << std::endl;
		std::cout << "Score: 0/1" << std::endl;
		return EXIT_FAILURE;
	}

	int score = 0;
	bool new_ref_ok = true;

	{
		System system(source_db.string());

		const TableInfo* table_info = catalog.get_table_info("valid_table");
		if (table_info == nullptr) {
			std::cout << "Error: table valid_table not found in source database." << std::endl;
			std::cout << "Score: 0/1" << std::endl;
			return EXIT_FAILURE;
		}

		HeapFile* heap_file = table_info->heap_file.get();
		const RID root_a(0, 0);
		const RID root_b(0, 3);
		std::vector<RID> roots = {root_a, root_b};

		std::map<RID, std::vector<RID>> chains;
		chains[root_a] = {root_a};
		chains[root_b] = {root_b};

		std::map<RID, RID> current_tip;
		current_tip[root_a] = root_a;
		current_tip[root_b] = root_b;

		const std::vector<RID> update_order = {
			root_a, root_b,
			root_a, root_b,
			root_a, root_b,
			root_a
		};

		const size_t updates_to_run = update_order.size();
		std::cout << "Running " << updates_to_run << " updates on valid_table..." << std::endl;

		for (size_t i = 0; i < updates_to_run; ++i) {
			const RID root_rid = update_order[i];
			const RID old_rid = current_tip[root_rid];
			const Record old_record = heap_file->get_record(old_rid);
			const auto old_header = heap_file->get_record_header(old_rid);

			if (old_record.invalid() || old_header.is_invalid()) {
				new_ref_ok = false;
				std::cout << "Skipping RID(" << old_rid.page_num << "," << old_rid.dir_slot
									<< ") because it is invalid." << std::endl;
				continue;
			}

			const Record updated_record = build_updated_record(old_record);
			const RID new_rid = heap_file->update(old_rid, updated_record, 0);
			chains[root_rid].push_back(new_rid);
			current_tip[root_rid] = new_rid;

			std::cout << "Update " << (i + 1) << " - old RID(" << old_rid.page_num << "," << old_rid.dir_slot
								<< ") -> new RID(" << new_rid.page_num << "," << new_rid.dir_slot << ")"
								<< " [root " << root_rid.page_num << "," << root_rid.dir_slot << "]" << std::endl;
		}

		std::cout << "Verifying first_rid references..." << std::endl;

		for (const RID& root_rid : roots) {
			const auto& chain = chains[root_rid];
			bool this_first_ref_ok = true;
			for (size_t i = 0; i + 1 < chain.size(); ++i) {
				const auto header = heap_file->get_record_header(chain[i]);
				if (header.is_invalid() || !(header.first == root_rid)) {
					this_first_ref_ok = false;
				}
			}

			const RID last_rid = chain.back();
			const auto last_header = heap_file->get_record_header(last_rid);
			const bool this_new_ref_ok =
				!last_header.is_invalid() &&
				(last_header.next == last_rid) &&
				(last_header.first == root_rid);
			this_first_ref_ok = this_first_ref_ok && this_new_ref_ok;

			if (!(this_new_ref_ok && this_first_ref_ok)) {
				new_ref_ok = false;
			}

			std::cout << "Chain from RID(" << root_rid.page_num << "," << root_rid.dir_slot << ") length "
								<< chain.size() << std::endl;
			std::cout << "  first_rid consistency and last refs: "
								<< ((this_new_ref_ok && this_first_ref_ok) ? "OK" : "FAIL") << std::endl;
		}
	}

	if (new_ref_ok) {
		score += 1;
	}

	std::cout << "Updated tuple refs check: " << (new_ref_ok ? "PASS (+1)" : "FAIL (+0)") << std::endl;
	std::cout << score << std::endl;

	return (score == 1) ? EXIT_SUCCESS : EXIT_FAILURE;
}
