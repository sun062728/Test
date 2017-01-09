#pragma once

#include <string>
#include <set>
#include <iostream>
#include "_predeclare.h"

namespace TestCopyControl {
	namespace RawPointer {
		class Message {
		public:
			Message(std::string const title, std::string const &msg)
				:title_(title), msg_(msg) {
			}
			Message(Message const &i);
			Message& operator=(Message const &r);
			~Message();
			void printMsg();
			void addFolder(Folder* const p);
			void delFolder(Folder* const p);
			friend void swap(Message &l, Message &r);
		private:
			void addSelfInFolders();
			void delSelfInFolders();
			std::string title_;
			std::string msg_;
			std::set<Folder*> folders_;
		};
	}
}