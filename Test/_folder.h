#pragma once

#include <string>
#include <set>
#include <iostream>
#include "_predeclare.h"

namespace TestCopyControl {
	namespace RawPointer {
		class Folder {
		public:
			Folder(std::string const &name)
				:name_(name) {
			}
			~Folder() {
			}
			void addMsg(Message* const p);
			void delMsg(Message* const p);
			void printAll();
			// forbid copy
			Folder(Folder const &r) = delete;
			Folder& operator=(Folder const &r) = delete;
		private:
			std::string name_;
			std::set<Message*> messages_;
		};

	}
}