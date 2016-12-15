#pragma once

#include <limits>

namespace TestConstexpr {
	int gInt = 1;
	int aaa = std::numeric_limits<int>::signaling_NaN();
	class LiteralType {
	public:
		constexpr LiteralType(int a, int b) // "constexpr" is must
		:a_(a), b_(b){
		}
		// hint compiler to do get during compile time
		constexpr inline int get() const {
			return 42;
		}
		inline int getLowest() {
			return std::numeric_limits<int>::lowest();
		}
	private:
		int a_, b_;
	};

	class TestConstexpr {
	public:
		void DoTest() {
			int i = 1;
			//constexpr int ceInt = i;
			constexpr int ceInt = 1;
			//constexpr int& iRef2 = ceInt;
			constexpr int& iRef = gInt; // gInt has FIXED address
			//constexpr int* p2 = &ceInt;
			constexpr int* p = &gInt; // constexpr T* == T* const, top level const

			int arg1 = 1, arg2 = 2;
			// constexpr A a = { arg1, arg2 };
			constexpr LiteralType a = { 1,2 }; 
			constexpr int ceInt2 = a.get();
			i = a.get();
			//i = a.getLowest(); // non-const member function
			i = std::numeric_limits<int>::lowest();

			LiteralType a1(1, 2);
			//constexpr int res = a1.get();
		}
	};
}