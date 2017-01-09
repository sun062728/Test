#pragma once

#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>

#include <sstream>

#include <string.h>  
#include <stdio.h>  

namespace TestString {
	// MS example
	void test_c_style() {
		char string1[] =
			"A string\tof ,,tokens\nand some  more tokens";
		char string2[] =
			"Another string\n\tparsed at the same time.";
		char seps[] = " ,\t\n";
		char *token1 = NULL;
		char *token2 = NULL;
		char *next_token1 = NULL;
		char *next_token2 = NULL;

		printf("Tokens:\n");

		// Establish string and get the first token:  
		token1 = strtok_s(string1, seps, &next_token1);
		token2 = strtok_s(string2, seps, &next_token2);

		// While there are tokens in "string1" or "string2"  
		while ((token1 != NULL) || (token2 != NULL))
		{
			// Get next token:  
			if (token1 != NULL)
			{
				printf(" %s\n", token1);
				token1 = strtok_s(NULL, seps, &next_token1);
			}
			if (token2 != NULL)
			{
				printf("        %s\n", token2);
				token2 = strtok_s(NULL, seps, &next_token2);
			}
		}
	}
	// there is no way to define multiple delimiters with stl!!!
	void test_cpp_style() {
		std::string string1("A string\tof ,,tokens\nand some  more tokens");
		std::string string2("Another string\n\tparsed at the same time.");
		std::string line;
		std::istringstream iss(string1);
		while (std::getline(iss, line, ' ')) {
			std::cout << line << std::endl;
		}
	}

	class A {
	public:
		A() = default;
		A(A const &a) {
			std::cout << "A copy ctor" << std::endl;
		}
		A(A &&a) {
			std::cout << "A move ctor" << std::endl;
		}
		void dump() {
			std::cout << "A::dump" << std::endl;
		}
	};

	void DoTest()
	{
		test_c_style();
		test_cpp_style();
		
	}
}