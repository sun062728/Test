#pragma once

#include <iostream>

namespace TestOperator {
	class A;
	class B {
	public:
		B() { }//std::cout << "B def ctor" << std::endl; }
		B(A const &a) { std::cout << "B gen from A" << std::endl; }
	};

	class A {
	public:
		A() = default;
		A(double d) { }
		A(float f) {}
		operator B() { std::cout << "A convert to B" << std::endl; return B(); }
	};

	void foo(B b) {

	}

	void DoTest() {
		A a;
		B b = a;

		foo(a);

		//A a1(1);
	}
}