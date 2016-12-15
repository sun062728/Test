#pragma once

namespace TestInitialization {
	void test_list_init() {
		//int a{ 3.14f }; // precision loss check is strict
		const int &ref = 4 * 2;
		int &i = const_cast<int&>(ref);
		i = 42;
	}
	void test_default_init() {

	}
	void DoTest(){
		test_list_init();
		test_default_init();
	}
}