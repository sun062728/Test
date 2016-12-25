#pragma once

#include <iostream>

// 6 sequential containers
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <array>
#include <string>

// Container adaptors
#include <stack>
#include <queue> // queue & priority_queue

namespace TestSequentialContainer {
	void DoTest() {
		std::deque<int> dq{ 0,1,2,3 };
		std::list<int> l{ 0,1,2,3 };
	}
}