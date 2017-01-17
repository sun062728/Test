#pragma once

#include <iostream>

namespace TestVirtualFunction {
	class A {
	public:
		virtual void foo(int i = 0) { std::cout << "A::foo, arg is " << i << std::endl; }
		void bar() { std::cout << "A::bar" << std::endl; }
	protected:
		void protected_func() {}
		int i_protected_;
	};
	class B :public A {
	public:
		virtual void foo(int i = 1) override { std::cout << "B::foo, arg is " << i << std::endl; }
		void bar() { std::cout << "B::bar" << std::endl; }
		void visit_base(A base) {
			//base.i_protected_;		// cannot visit protected member of base
			i_protected_;				// can visit "this" object's base
		}
	};

	void test_default_argument() {
		A *pA = new B();
		pA->foo();
		delete pA;
	}
	void test_avoid_dynamic_bind() {
		B *pB = new B();
		pB->A::bar();
		delete pB;
	}
	void DoTest() {
		test_default_argument();		// don't know why
		test_avoid_dynamic_bind();
	}
}