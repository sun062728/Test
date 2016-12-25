#pragma once

#include <iostream>

namespace TestInline {
	template<typename T>
	inline const T add(T l, T r) {
		return l + r;
	}

	class Addable {
	public:
		Addable(int i):i_(i) {
		}
		Addable(const Addable &a):i_(a.i_) {
		}
		Addable(Addable &&a) :i_(a.i_) {
		}
		~Addable() = default;
		const Addable& operator=(const Addable &rhs) {
			i_ = rhs.i_;
			return *this;
		}
		const Addable& operator=(Addable &&rhs) {
			i_ = rhs.i_;
			return *this;
		}
		inline friend const Addable operator+(const Addable &l, const Addable &r) {
			return Addable(l.i_ + r.i_);
		}
		int get() { return i_; }
	private:
		int i_;
	};
	void DoTest() {
		int i, j;
		i = 1; j = 4;
		//std::cin >> i >> j;
		Addable res = add<Addable>(Addable(i), Addable(j));
		std::cout << res.get() << std::endl;
	}
}