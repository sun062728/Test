#pragma once

#include <iterator>
#include <vector>
#include <string>

namespace TestIterator {
	void test_const_pointer() {
		typedef std::string *pStr;
		const std::string s("haha");
		//const pStr p = &s;			// high-level const
		const std::string *p = &s;	// low-level const
	}
	void test_const_iterator() {
		std::vector<int> ivec{ 0,1,2 };
		std::vector<int>::const_iterator cit = std::begin(ivec);
		*cit++;
		//(*cit)++;											// (*cit) is const
		//std::vector<int>::iterator it = std::cend(ivec);	// cend() returns constexpr
	}
	void DoTest() {
		test_const_pointer();
		test_const_iterator();
	}
}