#pragma once

#include <vector>
#include <string>
#include <string.h>

namespace TestTemplate {
	//template <typename T>
	//inline int compare(T const &i1, T const &i2) {
	//	if (i1 < i2) return -1;
	//	if (i1 > i2) return 1;
	//	return 0;
	//}

	template <typename T>
	inline int compare(T const &i1, T const &i2) {
		std::less<T> less_op;
		if (less_op(i1, i2))
			return -1;
		//if (std::less<T>()(i1, i2)) return -1;
		if (std::less<T>()(i2, i1)) return 1;

		return 0;
	}

	template<typename T, typename Fn_Less>
	inline int compare(T const &i1, T const &i2, Fn_Less Fn = Fn_Less()) {
		return Fn(i1, i2);
	}

	template<unsigned N, unsigned M>
	inline int compare(char const (&cstr1)[N], char const (&cstr2)[M]) {
		return strcmp(cstr1, cstr2);
	}

	class A {
	public:
		constexpr inline bool isOK() const {
			return true;
		}
	};

	class TestTemplate {
	public:
		void test_function_template() {
			compare(1, 2); compare<>(1, 2); compare<int>(1, 2);
			compare<int, std::less<int>>(1, 2);
		}
		void test_nontype_param() {
			char const str1[5] = "str1"; char const str2[6] = "str2";
			compare(str1, str2); compare<5, 6>(str1, str2);
		}
		void DoTest() {
			test_function_template();
			test_nontype_param();
		}
	};
}

