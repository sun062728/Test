#pragma once

#include <xutility>

template<typename F, typename... Args>
void PerfectForwarding(F &&func, Args&&...args)
{
	func(std::forward<Args>(args)...);
}

void foo(int&& i, float&& f)
{

}

class Logger
{
public:
	Logger() { std::cout << "def ctor" << std::endl; }
	Logger(int i_) { std::cout << "normal ctor" << std::endl; }
	~Logger() { std::cout << "dtor" << std::endl; }
	Logger(Logger const &rhs) { std::cout << "copy ctor" << std::endl; }
	Logger(Logger &&rhs){ std::cout << "move ctor" << std::endl; }
	Logger & operator=(Logger const &rhs) { std::cout << "copy assignment" << std::endl; }
	Logger & operator=(Logger &&rhs) { std::cout << "move assignment" << std::endl; }
	bool Release() { std::cout << "Release" << std::endl; return true; }
private:
	int i_;
};

class TestRvalueRef
{
public:
	Logger ReturnLogger() {
		Logger a(1), b(2);
		if (a.Release())
			return a;
		else
			return b;
	}
	void TestReturn() {
		Logger a = ReturnLogger();
	}
	void DoTest()
	{
		// lvalue_ref
		int lvalue = 1;
		int &lvalue_ref = lvalue;
		int &lvalue_ref2 = lvalue_ref;
		const int &lvalue_ref_c = 3;

		int &&rvalue_ref = 2;
		lvalue_ref = rvalue_ref;
		lvalue_ref = lvalue;
		const int &const_ref1 = rvalue_ref;

		// rvalue_ref
		//rvalue_ref = lvalue;
		//int &&rvalue_ref2 = rvalue_ref;
		
		// std::move
		rvalue_ref = std::move(lvalue);
		const int &const_ref2 = std::move(lvalue);
		// std::forward
		lvalue_ref = std::forward<int>(1);
		rvalue_ref = std::forward<int>(1);

		PerfectForwarding(foo, 1, 1.0f);

		TestReturn();
	}
};