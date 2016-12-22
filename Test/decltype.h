#pragma once

#include <initializer_list>
#include <vector>
#include <string>
#include <iterator>

namespace TestDecltype {
	const std::string foo(std::vector<std::string> strings) {
		auto			beg = std::begin(strings);
		decltype(beg)	end = std::end(strings);
		auto			size = end - beg;
		if (size)
			return std::string(*beg);
		else
			return "No string!";
	}

	void DoTest(){
		auto ret = foo({});
		ret = foo({ "haha", "hehe" });
	}
};