#pragma once

#include <iostream>
#include <cstdio>

namespace TestDataType {
	// c++ primer 5th, P37
	void TestChar() {
		const wchar_t* pWC = L"込込";		// (wchar_t)'0x54c8''0x54c8''00'
		//const char *pC = L"haha";			// Invalid wchar_t* -> char*
		//std::cout << *pWC << std::endl;	// *pWC convert to int
		const char* pU8 = u8"込込";			// (u8)'8893e5''8893e5''00'
		const char* pC = "込込";				// 'feb9''feb9''00'

		printf("%s\n", pWC);
		printf("%s\n", pU8);
		printf("%s\n", pC);
	}
	void DoTest() {
		TestChar();
	}
}