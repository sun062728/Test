#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <typeinfo>

class TestCast {
private:
	class A {
	public:
		virtual ~A() {
			std::cout << "A dtor" << std::endl;
		}
	};

	class B :public A {
	public:
		explicit B()
			:i_(0) {}
		B(int i)
			:i_(i) {}
		~B() override {
			std::cout << "B dtor" << std::endl;
		}
		explicit operator int() {
			return i_;
		}
		operator A() {
			std::cout << "B to A conversion" << std::endl;
		}
	private:
		int i_;
	};

	int test_b(B b) {
		return static_cast<int>(b);
	}

public:
	void test_arithmatic_conversion() {
		int i = 1; float f = 2.2;
		int res = i + f; // read asm
	}
	void test_dynamic_cast() {
		class C {};
		A* pA = new A; A* pAb = new B;
		B* pB = new B;
		C* pC = new C;

		B* pBb = dynamic_cast<B*>(pAb); // legal, classic
		A* pA2 = dynamic_cast<A*>(pB);  // legal

		B* pB2 = dynamic_cast<B*>(pA);  // NULL
		C* pC2 = dynamic_cast<C*>(pA);  // NULL
	}
	// static cast can be used on any well-defined(non-explicit) type conversion
	void test_static_cast() {
		int i = 42; float f = 42.1f; double d = 42.2;
		i = static_cast<int>(f); // implicit conversion, means we know precision loss

		A a; B b; A* pA = new B;
		a = static_cast<A>(b);
		//b = static_cast<B>(a); // base->derived is not safe

		B b2 = static_cast<B>(test_b(static_cast<B>(42)));
	}
	// const cast can only change const properties
	void test_const_cast() {
		int i = 1;
		const int& ci = 42;
		const_cast<int&>(ci) = i; // undefined, so bad bad
	}
	void test_reinterpret_cast() {
		int i = 42; char c = 'c';
		c = *reinterpret_cast<char*>(&i);
	}
	void func_param_cast(const B &in) {

	}
	void test_func_param_cast() {
		func_param_cast(2 /* B(2) */ ); // need non-explicit ctor
	}
	void DoTest() {
		test_arithmatic_conversion();
		test_dynamic_cast();
		test_static_cast();
		test_const_cast();
		test_reinterpret_cast();
		test_func_param_cast();
	}
};