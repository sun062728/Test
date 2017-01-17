#pragma once

#include <iostream>

namespace TestMove {
	class Nonmovable {
	public:
		Nonmovable() {
			std::cout << "Nonmovable default ctor" << std::endl;
		}
		Nonmovable(Nonmovable const &r) {
			std::cout << "Nonmovable copy ctor" << std::endl;
		}
		Nonmovable& operator=(Nonmovable const &r) {
			std::cout << "Nonmovable copy operator" << std::endl;
			return *this;
		}
		Nonmovable(Nonmovable &&m) = delete;
		Nonmovable& operator=(Nonmovable &&m) = delete;
		//{
		//	std::cout << "Nonmovable move assignment" << std::endl;
		//	return *this;
		//}
	};
	class Move {
	public:
		Move() = default;
		Move(Move &&r) = default;
		Move(Move const &m) {
			std::cout << "Move's copy ctor" << std::endl;
		}
		Move& operator=(Move &&m) = default;
		Move& operator=(Move const &r) = default;
	private:
		Nonmovable n_;
	};
	struct Movable {
		int i_;
	};
	class MoveOnly {
	public:
		MoveOnly() = default;
		MoveOnly(int i) {
			m_.i_ = i;
		}
		MoveOnly(MoveOnly &&m) = default;
		MoveOnly& operator=(MoveOnly &&m) = default;
		~MoveOnly() = default;
		MoveOnly(MoveOnly const &m) = delete;
		MoveOnly& operator=(MoveOnly const &m) = delete;
	private:
		Movable m_;
	};
	class NoCopy {
	public:
		NoCopy() = default;
		NoCopy(NoCopy &&m) {}
	};

	class CopyMove {
	public:
		CopyMove& operator=(CopyMove const &r) {
			return *this;
		}
		CopyMove& operator=(CopyMove &&m) {
			return *this;
		}
	};

	class Confusing {
	public:
		Confusing& operator=(Confusing c) {
			return *this;
		}
		Confusing& operator=(Confusing &&m) {
			return *this;
		}
	};

	class Limited {
	public:
		void foo() const &				// '&' is must because following function use &&, so we must define & or &&
		{
			std::cout << "lvalue" << std::endl;
		}
		void foo() const && {
			std::cout << "rvalue" << std::endl;
		}
	};

	void DoTest() {
		Move m1;
		Move m2(std::move(m1));
		m2 = std::move(m1);				// call default copy assignment instead, because default move assignment is deleted
										// if Nonmovable is movable, call default move assignment
										// custom move assignment can be called even when Nonmovable is contained

		MoveOnly mo1(1), mo2(2);
		MoveOnly mo3(std::move(mo1));	// call default move ctor
		mo2 = std::move(mo1);			// call default move assignment

		NoCopy nc1;
		NoCopy nc2(std::move(nc1));
		//nc2 = nc1;					// copy assignment is deleted since move ctor(or move assignment) is defined

		CopyMove cm1, cm2;
		cm1 = cm2;
		cm1 = std::move(cm2);

		Confusing cfs1, cfs2;
		//cfs1 = cfs2;					// operator=(Confusing const &) is deleted (???)
		//cfs1 = std::move(cfs2);		// ambiguous call (???)
										// compare with CopyMove

		Limited l1;
		l1.foo();
		std::move(l1).foo();
	}
}