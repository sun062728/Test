#pragma once

#include <algorithm>
#include <functional>
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>

namespace TestBind {
	class A {
	public:
		A():i_(42) {
			std::cout << "A default ctor" << std::endl;
		}
		A(A const &a):i_(a.i_) {
			std::cout << "A copy ctor" << std::endl;
		}
		int get() const { return i_; }
	private:
		int i_;
	};

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
		A a;
		auto passRef = [](A const &ref)->int {return ref.get(); };
		std::cout << "pass_value" << std::endl;
		auto pass_value = std::bind(passRef, a); // though passRef 1st arg is a reference, here a is threat as value
		pass_value();
		std::cout << "pass_ref" << std::endl;
		auto pass_ref = std::bind(passRef, std::ref(a));
		pass_ref();
	}
	void DoTest() {
		test_additional_args();
		test_reference_args();
	}
}