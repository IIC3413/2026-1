#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

/*
This test checks if the bytes of the file "0_to_test_table.tbl" match exactly with the bytes of the reference file "0_valid_table.tbl".
It reads both files as binary and compares their contents byte by byte.
If the files are identical, it prints a score of 2; otherwise, it prints a score of 0.

// TODO: Maybe use a metric of % of bytes that match with the reference file, instead of a binary score of 0 or 2.
// TODO: Test
*/


namespace fs = std::filesystem;

static bool read_file_bytes(const fs::path& path, std::vector<uint8_t>* bytes) {
	std::ifstream in(path, std::ios::binary);
	if (!in.is_open()) {
		return false;
	}

	in.seekg(0, std::ios::end);
	std::streamsize size = in.tellg();
	in.seekg(0, std::ios::beg);

	if (size < 0) {
		return false;
	}

	bytes->assign(static_cast<size_t>(size), 0);
	if (size > 0) {
		in.read(reinterpret_cast<char*>(bytes->data()), size);
	}

	return in.good() || in.eof();
}

int main() {
	int score = 0;

	const fs::path base_dir("data/example_db");
	const fs::path reference_file = base_dir / "0_valid_table.tbl";
	const fs::path test_file = base_dir / "0_to_test_table.tbl";

	if (!fs::exists(reference_file)) {
		std::cout << "Reference file not found: " << reference_file.string() << std::endl;
		std::cout << "Score: 0/1" << std::endl;
		return EXIT_FAILURE;
	}
	if (!fs::exists(test_file)) {
		std::cout << "Test file not found: " << test_file.string() << std::endl;
		std::cout << "Score: 0/1" << std::endl;
		return EXIT_FAILURE;
	}

	std::vector<uint8_t> reference_bytes;
	std::vector<uint8_t> test_bytes;

	if (!read_file_bytes(reference_file, &reference_bytes)) {
		std::cout << "Error reading reference file: " << reference_file.string() << std::endl;
		std::cout << "Score: 0/1" << std::endl;
		return EXIT_FAILURE;
	}
	if (!read_file_bytes(test_file, &test_bytes)) {
		std::cout << "Error reading test file: " << test_file.string() << std::endl;
		std::cout << "Score: 0/1" << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << "Reference file: " << reference_file.string() << " (" << reference_bytes.size()
						<< " bytes)" << std::endl;

	bool equal = true;
	if (reference_bytes.size() != test_bytes.size()) {
		equal = false;
		std::cout << "Size mismatch: expected " << reference_bytes.size() << " bytes, got " << test_bytes.size()
							<< " bytes." << std::endl;
	} else {
		for (size_t i = 0; i < reference_bytes.size(); ++i) {
			if (reference_bytes[i] != test_bytes[i]) {
				equal = false;
				std::cout << "First mismatch at byte " << i << ": expected " << static_cast<int>(reference_bytes[i])
									<< ", got " << static_cast<int>(test_bytes[i]) << std::endl;
				break;
			}
		}
	}

	if (equal) {
		score = 1;
		std::cout << score << std::endl;
	} else {
		std::cout << score << std::endl;
	}

	return equal ? EXIT_SUCCESS : EXIT_FAILURE;
}
