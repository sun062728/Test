#pragma once

#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

namespace TestAssociativeContainer {
	bool compare_string_size(const std::string &l, const std::string &r) {
		return l.size() < r.size();
	}

	void test_map() {
		// unary predicator
		std::map<int, int, std::less<int>> imap;
		for (int i = 0; i < 10; i++) {
			imap.insert({ i,i });
			imap.insert({ i,i });
		}
		auto four_lower_bound = imap.lower_bound(4);	// {4,4}
		++four_lower_bound;								// {5,5}
		auto four_upper_bound = imap.upper_bound(4);	// {5,5}
		
		// compare_string_size is not "strict weak ordering" (P378 on c++ primer 5th)
		//std::multimap<std::string, int, decltype(compare_string_size)*> smap;
		std::multimap<std::string, int> smap;
		smap.emplace("haha", 1);
		smap.emplace("hehe", 1);
		smap.emplace("heihei", 1);
		smap.emplace("hoho", 1);
		smap.emplace("hehe", 1);
		//smap.clear();
		auto num_hehe = smap.count("hehe");
		//smap.emplace({ "gaga", 1 });
		//smap.emplace_hint
		auto hehe_range = smap.equal_range("hehe");
		auto erase_hehe = smap.erase("hehe");
		auto it_haha = smap.find("haha");
		//smap.insert() // add entry
		smap.key_comp();
		auto hihi_lower_bound = smap.lower_bound("b"); // ->"haha", not end()!
		smap.value_comp();
		
		
	}
	// P391
	void test_word_convertion() {
		std::ifstream fRule("maptest_rule.txt"), fText("maptest_text.txt");
		std::map<std::string, std::string> ruleMap;
		for (std::string line; std::getline(fRule, line);) {
			auto first_space = line.find(' ', 0);
			std::string s1(line, 0, first_space);
			std::string s2(line, first_space + 1);
			ruleMap.insert({ s1,s2 });
		}
		for (std::string line; std::getline(fText, line);) {
			size_t word_head = 0, word_tail = 0;
			static auto do_map = [&line, &ruleMap](size_t b, size_t e) {
				std::string s(line, b, e - b);
				auto it = ruleMap.find(s);
				if (it != ruleMap.cend()) {
					std::cout << it->second << ' ';
				}
				else {
					std::cout << s << ' ';
				}
			};
			while (word_head < line.size()) {
				word_tail = line.find(' ', word_head);
				if (word_tail == std::string::npos)
					break;
				do_map(word_head, word_tail);
				word_head = word_tail + 1;
			}
			do_map(word_head, line.size());
			std::cout << std::endl;
		}
	}
	void DoTest() {
		test_map();
		test_word_convertion();
	}
}