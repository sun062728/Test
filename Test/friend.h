#pragma once

namespace TestFriend {
	class A {
	public:
		friend int friend_func(const A &a) { return a.i_;	}
	private:
		int i_;
	};
	
	void DoTest() {
		A a;
		int ci = friend_func(a);
	}
}