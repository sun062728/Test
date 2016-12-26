#pragma once

#include <algorithm>

#include <vector>
#include <string>
#include <list>

namespace TestAlgorithm {
	void DoTest() {
		std::list<int> ilist{ 4,2,7,4,8,6,32 };
		auto it = std::find(ilist.rbegin(), ilist.rend(), 4);
		if (it != ilist.rend()) {
			it++;
		}
	}
}