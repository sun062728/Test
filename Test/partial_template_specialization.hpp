#pragma once

#include <iostream>

namespace TestParitalTemplateSpecialization {
	template<typename T1, typename T2>
	class A {
	public:
		A() {
			std::cout << "A<T1, T2> ctor" << std::endl;
		}
		void foo() {}
	};

	template<typename T1>
	class A<T1, int> {
	public:
		A() {
			std::cout << "A<T1, int> ctor" << std::endl;
		}
	};

	void test_class() {
		A<char, char> a;
		A<char, int> b1;
		A<int, int> b2;
	}

	void test_member() {
		A<int, float> a;
		a.foo();
		A<float, float> b;
		b.foo();
	}

	void DoTest() {
		test_class();
		test_member();
	}
}