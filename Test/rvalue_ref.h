#pragma once

#include <xutility>

namespace TestRvalueRef {
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
		Logger(Logger &&rhs)
			:Logger() {
			swap(*this, rhs);
			std::cout << "move ctor" << std::endl; 
		}
		/*
		Logger & operator=(Logger rhs) {
			std::cout << "copy assignment" << std::endl;
			swap(*this, rhs);
			return *this; 
		}
		*/
		Logger & operator=(Logger &&rhs) {
			std::cout << "move assignment" << std::endl;
			swap(*this, rhs);
			return *this;
		}
		bool Release() const { std::cout << "Release" << std::endl; return true; }
		friend inline void swap(Logger &l, Logger &r) {
			std::swap(l.i_, r.i_);
		}
		void setI(int i) { i_ = i; }
	private:
		int i_;
	};

	Logger ReturnRVO() {
		return Logger(1);
	}
	Logger ReturnMove() {
		Logger a(2);
		return a;
	}
	Logger ReturnInput(Logger &l) {
		l.setI(3);
		return l;
	}
	void test_return() {
		std::cout << "Logger a = ReturnRVO();" << std::endl;
		Logger a = ReturnRVO();		// RVO
		std::cout << "Logger a1 = ReturnMove();" << std::endl;
		Logger a1 = ReturnMove();	// od: move, o2: RVO
		std::cout << "Logger b(a);" << std::endl;
		Logger b(a);				// copy ctor
		std::cout << "Logger c(std::move(a));" << std::endl;
		Logger c(std::move(a));		// move ctor
		std::cout << "c = std::move(a);" << std::endl;
		c = std::move(a);
		//c = a;
		std::cout << "Logger r = ReturnInput(ReturnMove());" << std::endl;
		Logger r = ReturnInput(ReturnMove());	// input arg l is the Rvalue return by ReturnMove()!!!
												// od: 2 move
												// o2: 1 RVO, then move
		std::cout << "END" << std::endl;
	}
	void test_rvalue_ref() {
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

	}
	void test_forward() {
		///int &lvalue_ref = std::forward<int>(1);
		int &&rvalue_ref = std::forward<int>(1);

		PerfectForwarding(foo, 1, 1.0f);
	}
	void DoTest()
	{
		test_rvalue_ref();
		test_forward();
		test_return();

		auto return_string = []()->std::string{
			std::string tmp("haha");
			return tmp;
		};

		std::string ret = return_string();
	}
}