#pragma once

#include <iterator>
#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <deque>
#include <fstream>

namespace TestIterator {
	// back_inserter, front_inserter, inserter
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
	// istream, ifstream
	void test_stream_iterator() {
		//std::istream_iterator<int> is_it(std::cin);
		//std::istream_iterator<int> eof;
		//while (is_it != eof) {
		//	std::cout << *is_it++ << std::endl;
		//}

		std::ifstream ifs("C:/Users/sun06/Desktop/Raster/cube.obj", std::ios::binary);
		std::istream_iterator<std::string> if_it(ifs);
		std::istream_iterator<std::string> eof;
		while (if_it != eof) {
			std::cout << *if_it++ << std::endl;
		}
	}
	void test_reverse_iterator() {
		std::string line("FIRST,MIDDLE,LAST");
		auto it_last_comma =std::find(line.crbegin(), line.crend(), ',');	// ->','
		auto comma_base = it_last_comma.base();								// ->'L'
		std::string last(comma_base, line.cend());
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