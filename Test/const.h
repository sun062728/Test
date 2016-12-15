#pragma once

#include <iostream>
#include <cstring>
#include <assert.h>

class Rational
{
public:
	explicit Rational(float f) :v_(f) {}
	Rational(Rational const &r):v_(r.v_) {}
	~Rational() { std::cout << "Rational dtor" << std::endl; }
	const Rational operator*(Rational const &rhs) const {
		Rational tmp(*this);
		tmp *= rhs;
		return tmp;
	}
	Rational& operator*=(Rational const &rhs) {
		v_ *= rhs.v_;
		return *this;
	}
	Rational& operator=(Rational const &rhs) {
		v_ = rhs.v_;
		return *this;
	}
	const float Get() const {
		return v_;
	}
private:
	float v_;
};

class String {
public:
	String() {}
	explicit String(char * const p) {
		char* pos = strchr(p, '\0');
		assert(pos);
		len_ = pos - p + 1;
		str_ = new char[len_];
		strcpy_s(str_, len_, p);
	}
	// client can modify String content
	char& operator[](size_t i) {
		assert(i < len_-1 && i>=0);
		return str_[i];
	}
	// String content modification is not allowed
	const char& operator[](size_t i) const {
		auto &c = const_cast<String&>(*this)[i];
		return const_cast<const char &>(c);
	}
	/* This is improper because client may modify return value of const String! */
	// char& operator[](size_t i) const
	char* c_str() const {
		return str_;
	}
	size_t length() const {
		return len_ - 1;
	}
private:
	char *str_;
	size_t len_;
};

String const & GetLonger(
	String const &a, 
	String const &b) {
	return a.length() >= b.length() ? a : b;
}

String & GetLonger(
	String &a,
	String &b) {
	auto &s = GetLonger(
		const_cast<String const &>(a),
		const_cast<String const &>(b));
	return const_cast<String &>(s);
}

class TestConst
{
public:
	void TestMemFn() {
		Rational a(1.2f), b(2.3f);
		/* Temp value is lvalue */
		//a*b = b;
		/* Temp value is destroyed after current expression */
		std::cout << "ptr: " << &(a*b) << std::endl;
		std::cout << a.Get() << std::endl;
	}
	void TestConstCast() {
		const int* const a = new int(1);
		const int* const b = const_cast<const int*const>(a);
		const int* c = const_cast<const int*>(b);
		c = a;
	}
	void TestLogicalConstness() {
		String a("a"), b("b");
		String r = GetLonger(a, b);
		char *p = &r[0];
		*p = 'c';
		String const ca("ca"), cb("cb1");
		String const cr = GetLonger(ca, cb);
		const char *cp = &cr[2];
		std::cout << "r: " << r.c_str() << std::endl;
		std::cout << "cr: " << cr.c_str() << std::endl;
	}
	void DoTest() {
		TestMemFn(); // nothing about const...
		TestConstCast();
		TestLogicalConstness();
	}
};