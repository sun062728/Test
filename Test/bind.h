#pragma once

#include <algorithm>
#include <functional>
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>

namespace TestBind {
	bool compare(const std::string &s, int size) {
		return s.size() >= size;
	}
	bool isShorter(const std::string s1, const std::string s2) {
		return s1.size() < s2.size();
	}
	void test_additional_args() {
		auto cmp5 = std::bind(compare, std::placeholders::_1, 5); // cmp5(s)

		std::vector<std::string> svec{ "the","quick","red","fox","jumps","over","the","slow","red","turtle" };
		std::stable_sort(svec.begin(), svec.end(), isShorter);
		std::stable_partition(svec.begin(), svec.end(), cmp5);
		for (const auto &s : svec) {
			std::cout << s.c_str() << ' ';
		}
		std::cout << std::endl;
	}
	void test_reference_args() {

	}
	void DoTest() {
		test_additional_args();
		test_reference_args();
	}
}