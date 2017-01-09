#include "_folder.h"
#include "_message.h"

using namespace TestCopyControl::RawPointer;

void Folder::addMsg(Message* const p) {
	messages_.insert(p);
	p->addFolder(this);
}
void Folder::delMsg(Message* const p) {
	messages_.erase(p);
	p->delFolder(this);
}
void Folder::printAll() {
	std::cout << "Folder name: " << name_ << std::endl;
	std::cout << "Messages:" << std::endl;
	for (auto &m : messages_) {
		std::cout << '\t';
		m->printMsg();
	}
}