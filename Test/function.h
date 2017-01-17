#pragma once

#include <functional>
#include <map>
#include <string>

// std::function can save functor, lambda and func ptr with identical "call signature"
namespace TestFunction {
	int minus(int a, int b) {
		return a - b;
	}
	class Divide {
	public:
		int operator()(int a, int b) {
			return a / b;
		}
	};
	void DoTest() {
		std::map<std::string, std::function<int(int, int)>> func_map = {
			{"+", std::plus<int>()},						// stl functor
			{"-", minus},									// function pointer
			{"*", [](int a,int b)->int {return a*b; }},		// lambda
			{"/", Divide()},								// custom functor
		};
		auto res = func_map["+"](1, 2);
	}
}