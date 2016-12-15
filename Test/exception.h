#pragma once

#include <iostream>
#include <exception>

class Thrower {
public:
	Thrower() {}
	~Thrower() {
		//throw std::exception("Thrower is throwing...");
	}
	void throw_exception() {
		throw std::exception("Thrower is throwing...");
	}
};

class TestException{
public:
	void TestThrowInDtor() {
		try {
			Thrower thrower;
			thrower.throw_exception();
		}
		catch(std::exception e){
			e.what();
		}
		catch (...) {

		}
	}
	void DoTest() {
		TestThrowInDtor();
	}
};