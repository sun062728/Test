#pragma once

#include <new>

namespace TestPlacementNew {
	class A {
	public:
		A():i_(0) {

		}
	private:
		int i_;
	};
	void DoTest() {
		char pBuffer[1024];
		A *p1 = new(pBuffer) A;
	}
}