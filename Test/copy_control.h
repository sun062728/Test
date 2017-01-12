#pragma once

#include <vector>
#include <string>
#include <set>
#include <memory>
#include <iostream>

// use common predeclare.h
// to avoid compiler error
#include "_folder.h"
#include "_message.h"

namespace TestCopyControl {
	namespace RawPointer {
		void DoTest() {
			Folder f1("Receiver"), f2("Litter Bin");
			Message msg1("Cesc", ""), msg2("Zero", "");
			msg1.addFolder(&f1); msg2.addFolder(&f2);
			f1.printAll(); f2.printAll();	// f1: cesc f2: zero
			Message msg3(msg1);
			f1.printAll(); f2.printAll();	// f1: cesc cesc f2: zero
			msg3 = msg2;
			f1.printAll(); f2.printAll();	// f1: cesc f2: zero zero
			msg3.delFolder(&f1);			// no change
			f1.printAll(); f2.printAll();
			msg3.delFolder(&f2);
			f1.printAll(); f2.printAll();	// f1: cesc f2: zero
		}
	}

	void DoTest() {
		RawPointer::DoTest();
	}
}