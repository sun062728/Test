#include <windows.h>

#include <iostream>
#include <memory>		// std::shared_ptr	std::unique_ptr		std::weak_ptr
#include <thread>		// std::thread		std::this_thread	std::thread_id
#include <functional>	// std::function	std::bind
#include <atomic>		// std::atomic_xxx
#include <mutex>		// std::mutex		std::lock_guard		std::unique_lock	std::condition_variable
#include <string>		// std::string

// algorithm
#include <vector>		// std::vector
#include <map>			// std::map
#include <stack>		// std::stack
#include <queue>		// std::queue
#include <deque>		// std::deque

// tests
#include "vector.h"
#include "rvalue_ref.h"
#include "singleton.h"
#include "shared_ptr.h"
#include "unique_ptr.h"
#include "weak_ptr.h"
#include "const.h"
#include "exception.h"
#include "cast.h"
#include "template.h"
#include "constexpr.h"
#include "data_type.h"
#include "initialization.h"

void main()
{
	//TestVector v; v.DoTest();
	//TestRvalueRef rr; rr.DoTest();
	//TestSingleton s; s.DoTest();
	//TestSharedPtr sp; sp.DoTest();
	//TestUniquePtr up; up.DoTest();
	//TestWeakPtr wp; wp.DoTest();
	//TestConst c; c.DoTest();
	//TestException test_exception; test_exception.DoTest();
	//TestCast cast; cast.DoTest();
	TestTemplate::TestTemplate tplt; tplt.DoTest();
	TestConstexpr::TestConstexpr ce; ce.DoTest();
	TestDataType::DoTest();
	TestInitialization::DoTest();

	return;
}