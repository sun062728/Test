#pragma once

#include <tuple>
#include <string>
#include <vector>
#include <iostream>

namespace TestTuple {
	void test_init() {
		std::tuple<std::string,
			std::vector<double>,
			int> res("", { 3.14f }, 1);
		std::tuple<std::string,
			std::vector<double>,
			int> res2{ "", { 3.14f }, 1 };
		std::tuple<std::string,
			std::vector<double>,
			int> res3 = { "", { 3.14f }, 1 };

		//auto make1 = std::make_tuple({ "",{ 3.14f }, 1 });
		auto make2 = std::make_tuple<std::string,std::vector<double>,int>("",{ 3.14f }, 1 );
		auto make3 = std::make_tuple("", 3.14f, 1);
	}
	void test_visit() {
		std::tuple<std::string,
			std::vector<double>,
			int> res("", { 3.14f }, 1);

		auto first = std::get<0>(res);
		auto second = std::get<1>(res);
		auto third = std::get<2>(res);
		std::cout << first << ' ' << second[0] << ' ' << third << std::endl;

		using ResType = decltype(res); // typedef decltype(res) ResType;
		auto element_num = std::tuple_size<ResType>::value;
		std::tuple_element<1, ResType>::type should_be_dvec = std::get<1>(res);
	}
	void test_compare() {
		std::tuple<std::string, std::string> twin1{ "haha", "hehe" };
		std::tuple<std::string, std::string> twin2{ "hehe", "haha" };
		std::tuple<std::string, std::string> twin3{ "hehe", "heihei" };

		if (twin1 < twin2) {
			if (twin2 == twin3) {
				std::cout << std::get<0>(twin3) << ' ' << std::get<1>(twin3) << std::endl;
			}
		}
	}
	void DoTest() {
		test_init();
		test_visit();
		test_compare();
	}
}