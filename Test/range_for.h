#pragma once

#include <vector>
#include <iterator>

namespace TestRangeFor {
	void test_range_for(std::vector<int> const &ivec) {
		for (const auto &i : ivec) {
			;
		}
	}
	void test_range_for_simulator(std::vector<int> const &ivec) {
		for (auto beg = ivec.begin(), end = ivec.end(); beg != end; ++beg) {
			const auto &i = *beg;
		}
	}
	void DoTest() {
		test_range_for({ 0, 1, 2 });
		test_range_for_simulator({ 0, 1, 2 });
	}
}