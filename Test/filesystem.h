#pragma once

// C++17 feature

#include <filesystem>
//#include <experimental\filesystem>
#include <iostream>

namespace TestFileSystem {
	using namespace std::experimental;
	void test_copy() {
		filesystem::copy("D:/test1.txt", "D:/test2.txt", filesystem::copy_options::overwrite_existing);
	}
	void test_visit_dir() {
		for (auto it = filesystem::recursive_directory_iterator("D:/SymbolCache"); it != filesystem::recursive_directory_iterator(); ++it)
		{
			std::cout << it->path() << std::endl;
		}
	}
	void DoTest() {
		test_copy();
		test_visit_dir();
	}
}