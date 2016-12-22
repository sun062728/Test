#pragma once

#include <string>
#include <typeinfo>
#include <iostream>

namespace TestInitialization {
	class A {
	public:
		A() {}
		A(int i, const std::string &s)
		:i_(i), s_(s){}
	private:
		int i_ = 1;
		std::string s_ = "haha";
	};

	//void vec(std::initializer_list<int> list) {	}
	void vec(std::vector<float> fvec) {	}
	void vec(std::vector<int> ivec) { }
	void test_initializer_list() {
		//int a{ 3.14f }; // precision loss check is strict
		auto list = { 1,2,3 };
		std::cout << "typeid of list is: " << typeid(decltype(list)).name() << std::endl;
		vec(list); // vec(ivec), cuz initializer_list is strict
		//vec({ 1,2,3 }); // ambiguous call
	}
	void test_default_init() {

	}
	void test_in_class_initializer() {
		A a1, a2(2, "hehe");
	}
	void DoTest(){
		test_initializer_list();
		test_default_init();
		test_in_class_initializer();
	}
}