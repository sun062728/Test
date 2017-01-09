#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

namespace TestSwap {
	class HasPtr {
	public:
		HasPtr(std::string const &s = std::string())
			:ps_(new std::string(s)), use_(new std::size_t(1)), i_(0){ 
		}
		HasPtr(HasPtr const &r)
			:ps_(r.ps_), i_(r.i_), use_(r.use_) {
			(*use_)++;
		}
		~HasPtr() {
			if (--(*use_) == 0) {
				delete ps_;
				delete use_;
			}
		}
		HasPtr& operator=(HasPtr const &r) {
			(*r.use_)++;
			if ((*use_)-- == 0) {
				delete ps_;
				delete use_;
			}
			ps_ = r.ps_;
			i_ = r.i_;
			use_ = r.use_;
			return *this;
		}
		friend inline bool operator<(HasPtr const &l, HasPtr const &r) {
			return (*l.ps_) < (*r.ps_);
		}
		friend inline void swap(HasPtr &l, HasPtr &r) {
			using std::swap;
			swap(l.ps_, r.ps_);
			swap(l.i_, r.i_);
			swap(l.use_, r.use_);
		}
	private:
		std::string *ps_;
		std::size_t *use_;
		int i_;
	};
	void DoTest() {
		std::vector<HasPtr> vec(64);

		std::sort(vec.begin(), vec.end());
	}
}