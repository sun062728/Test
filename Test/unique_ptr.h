#pragma once

#include <memory>
#include <iostream>

class CustomUPDeletor
{
public:
	CustomUPDeletor() {}
	~CustomUPDeletor() {}
	void Release(CustomUPDeletor *) { std::cout << "Release Customized" << std::endl; }
};

void Release(CustomUPDeletor *) {

}

class TestUniquePtr
{
public:
	template<typename T>
	std::unique_ptr<T> MakeUniquePtr(T *t) {
		return std::unique_ptr<T>(t);
	}
	void TestCtor() {
		std::unique_ptr<int> pDefault;
		std::unique_ptr<int> pExplicit(new int(42));
		std::unique_ptr<int> pMoveCtor = MakeUniquePtr<int>(new int(42));
		//std::unique_ptr<int> pImplicit = new int(42);
		//std::unique_ptr<int> pCopyCtor(pDefault);		
	}
	void TestCopy() {
		std::unique_ptr<int> p1;
		std::unique_ptr<int> p2(new int(42));
		//p1 = p2;
		p2 = nullptr; // call reset()
	}
	void TestMove() {
		std::unique_ptr<int> p1;
		std::unique_ptr<int> p2(new int(42));
		p1.reset(p2.release()); // p1 take over p2
		p2 = MakeUniquePtr<int>(new int(42));
	}
	// not fully understand yet
	void TestDeleter() {
		std::unique_ptr<CustomUPDeletor> p1;
		///std::unique_ptr<CustomUPDeletor, decltype(std::mem_fn(CustomUPDeletor::Release))*> p2(new CustomUPDeletor, std::mem_fn(CustomUPDeletor::Release));
		std::unique_ptr<CustomUPDeletor, decltype(Release)*> p2(new CustomUPDeletor, Release);
	}
	void DoTest() {
		TestCtor();
		TestCopy();
		TestMove();
		TestDeleter();
	}
};