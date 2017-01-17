#pragma once

#include <algorithm>
#include <iostream>
#include <string>

namespace TestLambda {
	class ReturnInt {
	public:
		ReturnInt(int const &i)
			:ref_(i) {
		}
		int operator()(void) {
			return ref_;
		}
	private:
		int const &ref_;
	};
	// lambda is function object
	// capture list is stored in object's member variable
	void test_lambda_size() {
		std::string s("haha");
		auto stringSize = sizeof(s);

		auto empty = []()->void{};
		auto captureValue = [s]()->void {return; };
		auto captureRef = [&s]()->void {return; };
		auto size = sizeof(empty);
		size = sizeof(captureValue);
		size = sizeof(captureRef);		// capture 1 ref, size is 4

		int ci = 1;
		ReturnInt op(ci);
		int ret = op();
		size = sizeof(op);				// functor with 1 ref member, size is 4
	}
	void test_lambda_capture() {
		int a, b, c, d;
		a = b = c = d = 0;
		auto explicit_capture = [&a, &b, &c, &d] {a++, b++, c++, d++; };
		auto implicit_capture_ref = [&] {a++, b++, c++, d++; };
		auto implicit_capture_value = [=] {a; b; c; d; }; // cannot assign
		auto capture_mutable = [=]() mutable {a++, b++, c++, d++; };
		
		auto print = [&] {std::cout << "a " << a << " b " << b << " c " << c << " d " << d << std::endl; };
		explicit_capture();		print(); // change ref
		implicit_capture_ref();	print(); // change ref
		capture_mutable();		print(); // only make capture value mutable, doesn't influence outside variables
	}
	void DoTest() {
		test_lambda_size();
		test_lambda_capture();
	}
}