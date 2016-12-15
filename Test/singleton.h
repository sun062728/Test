#pragma once

#include <iostream>
#include <mutex>
#include <memory>

class SingletonStatic final
{
public:
	static SingletonStatic & Instance()
	{
		static SingletonStatic instance;
		return instance;
	}

	void print()
	{
		std::cout << "SingletonStatic" << std::endl;
	}
private:
	SingletonStatic() { std::cout << "SS ctor! Handle: 0x"<< this << std::endl; }
	~SingletonStatic() { std::cout << "SS dtor!" << std::endl; }
	SingletonStatic(SingletonStatic const &) = delete;
	SingletonStatic(SingletonStatic &&) = delete;
	SingletonStatic operator=(SingletonStatic const &) = delete;
	SingletonStatic operator=(SingletonStatic &&) = delete;

};

class SingletonDoubleCheck final
{
public:
	static SingletonDoubleCheck & Instance()
	{
		if (instance_ == nullptr) {
			std::lock_guard<std::mutex> l(mutex_);
			if (instance_ == nullptr) {
				instance_ = new SingletonDoubleCheck;
				std::cout << "New Double Check!";
				std::cout << " Handle: 0x" << instance_ << std::endl;
			}
		}
		return *instance_;
	}

	static void Release()
	{
		if (instance_ != nullptr) {
			std::lock_guard<std::mutex> l(mutex_);
			if (instance_ != nullptr) {
				delete instance_;
				instance_ = nullptr;
				std::cout << "Release SDC!" << std::endl;
			}
		}
	}

private:
	static SingletonDoubleCheck* instance_;
	static std::mutex mutex_;

	SingletonDoubleCheck() {}
	~SingletonDoubleCheck() {}
	SingletonDoubleCheck(SingletonDoubleCheck const &) = delete;
	SingletonDoubleCheck(SingletonDoubleCheck &&) = delete;
	SingletonDoubleCheck operator=(SingletonDoubleCheck const &) = delete;
	SingletonDoubleCheck operator=(SingletonDoubleCheck &&) = delete;
};

SingletonDoubleCheck* SingletonDoubleCheck::instance_ = nullptr;
std::mutex SingletonDoubleCheck::mutex_;

template<typename T>
class Singleton
{
private:
	Singleton(Singleton const &) = delete;
	Singleton(Singleton &&) = delete;
	Singleton operator=(Singleton const &) = delete;
	Singleton operator=(Singleton &&) = delete;
protected:
	Singleton() {}
	~Singleton() {}
public:
	static T& Instance()
	{
		static T inst;
		return inst;
	}
};

class SingleObject :public Singleton<SingleObject>
{
public:
	SingleObject() {}
	~SingleObject() {}
private:
	int stub_;
};

class TestSingleton
{
public:
	void DoTest()
	{
		SingletonStatic& ss = SingletonStatic::Instance();
		ss.print();

		SingletonDoubleCheck& sdc = SingletonDoubleCheck::Instance();
		SingletonDoubleCheck& sdc2 = SingletonDoubleCheck::Instance();
		SingletonDoubleCheck::Release();
		SingletonDoubleCheck::Release();

		SingleObject::Instance();
	}
};