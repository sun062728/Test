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
	void test_size() {
		std::vector<int> ivec{ 0,1,2,3,4,5,6,7,8,9 };
		auto cap = ivec.capacity();
		auto size = ivec.size();
		auto max_size = ivec.max_size();

		ivec.erase(ivec.end() - 1);
		cap = ivec.capacity();
		size = ivec.size();
		max_size = ivec.max_size();

		ivec.reserve(20);
		cap = ivec.capacity();
		size = ivec.size();
		max_size = ivec.max_size();

		ivec.shrink_to_fit();
		cap = ivec.capacity();
		size = ivec.size();
		max_size = ivec.max_size();
	}
	void test_assignment() {
		std::vector<int> ivec1{ 0,1,2,3,4,5,6,7,8,9 };
		std::vector<int> ivec2(ivec1.rbegin(), ivec1.rend());

		std::swap(ivec1, ivec2);

		std::vector<double> dvec{ 9.8,5.8,2.4,6.2 };
		ivec1.assign(dvec.begin(), dvec.end()); // 1. clear 2. assign

		auto back = ivec1.back();
		auto pData = ivec1.data();
		ivec1.erase(ivec1.begin() + 1);
		ivec1.clear();
	}
	void DoTest() {
		test_vector_of_ref();
		test_size();
		test_assignment();
	}
}