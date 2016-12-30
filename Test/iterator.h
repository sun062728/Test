#pragma once

#include <iterator>
#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <deque>

namespace TestIterator {
	void test_insert_iterator() {
		std::deque<int> ideq{ 3,4,5 };
		auto back_it = std::back_inserter(ideq);
		*back_it = 100;
		assert(*ideq.rbegin() == 100);
		// 3 4 5 100
		auto front_it = std::front_inserter(ideq);
		*front_it = 200;
		assert(*ideq.begin() == 200);
		// 200 3 4 5 100
		auto insert_it = std::inserter(ideq, ideq.begin() + ideq.size() / 2);
		*insert_it = 500;
		// 200 3 500 4 5 100
	}
	void test_stream_iterator() {
		std::istream_iterator<int> is_it(std::cin);

	}
	void test_reverse_iterator() {

	}
	void test_move_iterator() {

	}
	void DoTest() {
		test_insert_iterator();
		test_stream_iterator();
		test_reverse_iterator();
		test_move_iterator();
	}
}