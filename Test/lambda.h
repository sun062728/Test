#pragma once

#include <algorithm>
#include <iostream>
#include <string>

namespace TestLambda {
	// lambda should better be considered as function object
	// capture list is stored in object's member variable
	void test_lambda_size() {
		std::string s("haha");
		auto stringSize = sizeof(s);

		auto captureValue = [s]()->void {return; };
		auto captureRef = [&s]()->void {return; };
		auto size = sizeof(captureValue);
		size = sizeof(captureRef);
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