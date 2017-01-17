#pragma once

// A predeclare header for all headers
// To avoid including dependencies of those headers
// included by:
// _folder.h
// _message.h
namespace TestCopyControl {
	namespace RawPointer {
		class Folder;
		class Message;
	}
}