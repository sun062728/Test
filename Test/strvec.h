/*
** P464 c++ primer 5th
*/

#pragma once

#include <string>
#include <allocators>
#include <algorithm> 

namespace TestStrVec {
	class StrVec {
	public:
		StrVec()
			:elements(nullptr), first_free(nullptr), cap(nullptr) {
		}
		StrVec(const StrVec &s) {
			auto pair = alloc_n_copy(s.begin(), s.end());
			elements = pair.first;
			first_free = cap = pair.second;
		}
		StrVec& operator=(const StrVec &r) {
			auto pair = alloc_n_copy(r.begin(), r.end());
			free();
			elements = pair.first;
			first_free = cap = pair.second;
			return *this;
		}
		~StrVec() {
			free();
		}
		void push_back(const std::string &s) {
			chk_n_alloc();
			alloc.construct(first_free++, s);
		}
		std::size_t size() const {
			return first_free - elements;
		}
		std::size_t capacity() const {
			return cap - elements;
		}
		std::string* begin() const {
			return elements;
		}
		std::string* end() const {
			return first_free;
		}
	private:
		static std::allocator<std::string> alloc;
		void chk_n_alloc() {
			if (size() == capacity())
				reallocate();
		}
		std::pair<std::string *, std::string *> alloc_n_copy(const std::string *b, const std::string *e) {
			auto beg = alloc.allocate(e - b);
			auto end = std::uninitialized_copy(b, e, beg);
			return{ beg, end };
		}
		void free() {
			if (elements) {
				for (auto it = first_free; it != elements; it--) {
					alloc.destroy(it);
				}
				alloc.deallocate(elements, cap - elements);
			}
		}
		void reallocate() {
			auto new_cap = size() ? size() * 2 : 1;
			auto new_beg = alloc.allocate(new_cap);
			auto sz = size();
			for (auto it = new_beg; elements != first_free; elements++, it++) {
				alloc.construct(it, std::move(*elements));
			}
			free();
			elements = new_beg;
			first_free = new_beg + sz;
			cap = new_beg + new_cap;
		}
		std::string *elements;
		std::string *first_free;
		std::string *cap;
	};
	void DoTest() {

	}
}