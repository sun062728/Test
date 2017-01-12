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
			:elements_(nullptr), first_free_(nullptr), cap_(nullptr) {
		}
		StrVec(const StrVec &s) {
			auto pair = alloc_n_copy(s.begin(), s.end());
			elements_ = pair.first;
			first_free_ = cap_ = pair.second;
		}
		StrVec(StrVec &&r) noexcept {
			elements_ = r.elements_;
			cap_ = r.cap_;
			first_free_ = r.first_free_;
			r.elements_ = r.cap_ = r.first_free_ = nullptr;
		}
		StrVec& operator=(const StrVec &r) {
			auto pair = alloc_n_copy(r.begin(), r.end());
			free();
			elements_ = pair.first;
			first_free_ = cap_ = pair.second;
			return *this;
		}
		StrVec& operator=(StrVec &&r) noexcept {
			if (this != &r) {
				free();
				elements_ = r.elements_;
				cap_ = r.cap_;
				first_free_ = r.first_free_;
				r.elements_ = r.cap_ = r.first_free_ = nullptr;
			}
			return *this;
		}
		~StrVec() {
			free();
		}
		void push_back(const std::string &s) {
			chk_n_alloc();
			alloc.construct(first_free_++, s);
		}
		std::size_t size() const {
			return first_free_ - elements_;
		}
		std::size_t capacity() const {
			return cap_ - elements_;
		}
		std::string* begin() const {
			return elements_;
		}
		std::string* end() const {
			return first_free_;
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
			if (elements_) {
				for (auto it = first_free_; it != elements_; it--) {
					alloc.destroy(it);
				}
				alloc.deallocate(elements_, cap_ - elements_);
			}
		}
		void reallocate() {
			auto new_cap = size() ? size() * 2 : 1;
			auto new_beg = alloc.allocate(new_cap);
			auto sz = size();
			for (auto it = new_beg; elements_ != first_free_; elements_++, it++) {
				alloc.construct(it, std::move(*elements_));
			}
			free();
			elements_ = new_beg;
			first_free_ = new_beg + sz;
			cap_ = new_beg + new_cap;
		}
		std::string *elements_;
		std::string *first_free_;
		std::string *cap_;
	};
	void DoTest() {

	}
}