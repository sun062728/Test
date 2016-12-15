#pragma once

class TestVector final
{
public:
	TestVector() {}
	TestVector(const TestVector &) = delete;
	TestVector(TestVector &&) = delete;
	~TestVector() {}
	TestVector operator=(TestVector const &) = delete;
	TestVector operator=(TestVector &&) = delete;
	void DoTest()
	{
		auto f = []() {return 1; };
	}
};