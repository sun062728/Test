#include <windows.h>

#include <iostream>
#include <memory>		// std::shared_ptr	std::unique_ptr		std::weak_ptr
#include <thread>		// std::thread		std::this_thread	std::thread_id
#include <functional>	// std::function	std::bind
#include <atomic>		// std::atomic_xxx
#include <mutex>		// std::mutex		std::lock_guard		std::unique_lock	std::condition_variable

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
#include "decltype.h"
#include "range_for.h"
#include "iterator.h"
#include "tuple.h"
#include "bitset.h"
#include "inline.h"
#include "algorithm.h"
#include "lambda.h"
#include "bind.h"
#include "filesystem.h"
#include "thread.h"
#include "leetcode.h"
#include "associative_container.h"
#include "string.h"
#include "text_query_prog.h"
#include "swap.h"
#include "copy_control.h"
#include "move.h"
#include "strvec.h"
#include "function.h"
#include "operator.h"
#include "virtual_function.h"
#include "text_query_prog_ch15.h"
#include "partial_template_specialization.hpp"
#include "placement_new.h"

void main()
{
	//TestVector::DoTest();
	TestRvalueRef::DoTest();
	//TestSingleton s; s.DoTest();
	//TestSharedPtr sp; sp.DoTest();
	//TestUniquePtr up; up.DoTest();
	//TestWeakPtr wp; wp.DoTest();
	//TestConst c; c.DoTest();
	//TestException test_exception; test_exception.DoTest();
	//TestCast cast; cast.DoTest();
	TestTemplate::TestTemplate tplt; tplt.DoTest();
	//TestConstexpr::TestConstexpr ce; ce.DoTest();
	//TestDataType::DoTest();
	//TestInitialization::DoTest();
	//TestDecltype::DoTest();
	//TestRangeFor::DoTest();
	TestIterator::DoTest();
	//TestTuple::DoTest();
	//TestBitset::DoTest();
	//TestInline::DoTest();
	TestAlgorithm::DoTest();
	TestLambda::DoTest();
	TestBind::DoTest();
	//TestFileSystem::DoTest();
	//TestThread::DoTest();
	//TestLeetCode::DoTest();
	TestAssociativeContainer::DoTest();
	TestString::DoTest();
	//TextQueryProg::DoTest();
	TestSwap::DoTest();
	TestCopyControl::DoTest();
	TestMove::DoTest();
	TestStrVec::DoTest();
	TestFunction::DoTest();
	TestOperator::DoTest();
	TestVirtualFunction::DoTest();
	///TestTextQueryProgCh15::DoTest();
	TestParitalTemplateSpecialization::DoTest();
	TestPlacementNew::DoTest();
	
	return;
}