#pragma once

#include <vector>
#include <iterator>

namespace TestVector {
	// reference is not object
	// so vector of reference doesn't exist
	// --- c++ primer 5th p87
	void test_vector_of_ref() {
		//std::vector<int&> ref_vec; // pointer to reference is illegal
	}
	void DoTest() {
		void test_vector_of_ref();
	}
}