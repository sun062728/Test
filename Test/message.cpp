#include "_message.h"
#include "_folder.h"

using namespace TestCopyControl::RawPointer;

Message::Message(Message const &i)
	:title_(i.title_), msg_(i.msg_), folders_(i.folders_) {
	addSelfInFolders();
}

Message& Message::operator=(Message const &r) {
	delSelfInFolders();
	title_ = r.title_;
	msg_ = r.msg_;
	folders_ = r.folders_;
	addSelfInFolders();
	return *this;
}

Message::~Message() {
	delSelfInFolders();
}

void Message::printMsg() {
	std::cout << title_ << std::endl;
}

void Message::addFolder(Folder* const p) {
	folders_.insert(p);
}

void Message::delFolder(Folder* const p) {
	folders_.erase(p);
}

void TestCopyControl::RawPointer::swap(Message &l, Message &r) {
	using std::swap;
	l.delSelfInFolders();
	r.delSelfInFolders();
	swap(l.folders_, r.folders_);
	swap(l.msg_, r.msg_);
	swap(l.title_, r.title_);
	l.addSelfInFolders();
	r.addSelfInFolders();
}

void Message::addSelfInFolders() {
	for (auto &f : folders_)
		f->addMsg(this);
}

void Message::delSelfInFolders() {
	for (auto &f : folders_)
		f->delMsg(this);
}
