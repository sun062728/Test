#pragma once

#include <bitset>
#include <iostream>

namespace TestBitset {
	void test_init() {
		std::bitset<33> bits(~0ULL);
		std::cout << bits.to_string() << std::endl;

		std::bitset<33> bits2("11111""11111""11111""11111""11111""11111""10"); // 32 bits
		std::cout << bits2.to_string() << std::endl;
	}
	void test_function() {

	}
	void DoTest() {
		test_init();
		test_function();
	}
}