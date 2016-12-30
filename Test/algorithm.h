#pragma once

// sort
// find, find_if
// partition
// for_each
#include <algorithm>

#include <vector>
#include <string>
#include <list>

namespace TestAlgorithm {
	void print_svec(std::vector<std::string>::const_iterator cbeg,
		std::vector<std::string>::const_iterator cend) {
		while (cbeg != cend) {
			std::cout << *cbeg++ << std::endl;
		}
		std::cout << std::endl;
	}
	template<int SIZE>
	bool is_string_greater_equal_size(std::string s) {
		return s.size() >= SIZE;
	}
	bool is_string_greater_equal_5(std::string s) {
		return s.size() >= 5;
	}
	bool isShorter(const std::string &l, const std::string &r) {
		return l.size() < r.size();
	}
	void elimDups(std::vector<std::string> &svec) {
		std::sort(svec.begin(), svec.end());
		auto unique_end = std::unique(svec.begin(), svec.end());
		svec.erase(unique_end, svec.end());
	}
	void biggies_5(std::vector<std::string> &svec) {
		elimDups(svec);
		auto it_less_5 = std::partition(svec.begin(), svec.end(), is_string_greater_equal_size<5>);
		print_svec(svec.cbegin(), it_less_5);
		//print_svec(svec.cbegin(), svec.cend());
	}
	void biggies(std::vector<std::string> &svec,
		std::vector<std::string>::size_type sz) {
		elimDups(svec);
		print_svec(svec.cbegin(), svec.cend());
		std::stable_sort(svec.begin(), svec.end(), isShorter);
		print_svec(svec.cbegin(), svec.cend());
	}
	void test_some_algorithms() {
		std::vector<std::string> svec{ "the","quick","red","fox","jumps","over","the","slow","red","turtle" };
		//biggies_5(svec);
		biggies(svec, 5);
		int size = 4;
		auto it = std::find_if(svec.cbegin(), svec.cend(),
			[size](const std::string &s)->bool {
			return s.size() >= size; });
	}
	// list algorithms should call its member functions
	void test_list_algorithms() {
		std::list<int> ilist{35,76,7,3,52,54,36,5,475,4,7};
		std::list<int> headlist{ 100 };
		ilist.sort();
		ilist.remove(475);
		ilist.splice(ilist.begin(), headlist);
		ilist.reverse();
		ilist.unique();
	}
	void DoTest() {
		test_some_algorithms();
		test_list_algorithms();
	}
}