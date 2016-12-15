#pragma once

#include <memory>
#include <iostream>

class TestWeakPtr
{
public:
	void Observe(std::weak_ptr<int> const &wp) {
		if (auto sp = wp.lock())
			std::cout << "wp: " << *sp.get() << std::endl;
		else
			std::cout << "wp is null" << std::endl;
	}

	void TestCtor() {
		std::weak_ptr<int> pDefault;
		std::weak_ptr<int> pCopyCtor(pDefault);
		std::weak_ptr<int> pMoveCtor(std::move(pDefault));
		std::shared_ptr<int> pShared = std::make_shared<int>(42);
		std::weak_ptr<int> pInitShared(pShared);
	}

	void TestUse() {
		std::weak_ptr<int> wp;
		Observe(wp);
		{
			std::shared_ptr<int> sp = std::make_shared<int>(42);
			wp = sp;
			Observe(wp);
		}
		Observe(wp);
	}

	// NO memory leak
	void TestCircularReference() {
		struct Node
		{
			Node(std::string name) { this->name = name; }
			~Node() { std::cout << "Node " << name.c_str() << "'s dtor" << std::endl; }
			std::weak_ptr<Node> prev;
			std::shared_ptr<Node> next;
			std::string name;
		};

		std::shared_ptr<Node> head = std::make_shared<Node>("Head");
		std::shared_ptr<Node> tail = std::make_shared<Node>("Tail");
		head->next = tail;
		tail->prev = head; tail->next = nullptr;
	}

	void DoTest() {
		TestCtor();
		TestUse();
		TestCircularReference();
	}
};