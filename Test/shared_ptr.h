#pragma once

#include <iostream>
#include <memory>

class CustomSPDeletor
{
public:
	CustomSPDeletor() {};
	~CustomSPDeletor() { std::cout << "Dtor of Customized" << std::endl; };

	void Release() { std::cout << "Release Customized" << std::endl; }
};

class TestSharedPtr final
{
public:
	void TestCtor() {
		std::shared_ptr<int> pDefault;
		std::shared_ptr<int> pExplicit(new int(42));
		std::shared_ptr<int> pMoveCtor = std::make_shared<int>(42);
		std::shared_ptr<int> pCopyCtor = pMoveCtor;
		//std::shared_ptr<int> pImplicit = new int(42);
	}
	void TestCopy() {
		std::shared_ptr<int> p1 = std::make_shared<int>(1);
		std::shared_ptr<int> p2 = std::make_shared<int>(22);
		std::cout << "p1: " << *p1.get() << " Count: " << p1.use_count() << std::endl;
		std::cout << "p2: " << *p2.get() << " Count: " << p2.use_count() << std::endl;
		p1 = p2;
		std::cout << "p1 = p2;" << std::endl;
		std::cout << "p1: " << *p1.get() << " Count: " << p1.use_count() << std::endl;
		std::cout << "p2: " << *p2.get() << " Count: " << p2.use_count() << std::endl;
	}
	void TestDeleter() {
		std::shared_ptr<CustomSPDeletor> pC(new CustomSPDeletor(), std::mem_fn(&CustomSPDeletor::Release));
		std::shared_ptr<CustomSPDeletor> pC2(pC);
	}
	void TestSwap() {
		std::shared_ptr<int> p1 = std::make_shared<int>(1);
		std::shared_ptr<int> p2 = std::make_shared<int>(22);
		std::cout << "p1: " << *p1.get() << " Count: " << p1.use_count() << std::endl;
		std::cout << "p2: " << *p2.get() << " Count: " << p2.use_count() << std::endl;
		p1.swap(p2);
		std::cout << "p1.swap(p2);" << std::endl;
		std::cout << "p1: " << *p1.get() << " Count: " << p1.use_count() << std::endl;
		std::cout << "p2: " << *p2.get() << " Count: " << p2.use_count() << std::endl;
	}
	void TestUnique() {
		std::shared_ptr<int> p1 = std::make_shared<int>(1);
		std::shared_ptr<int> p2 = std::make_shared<int>(22);
		if (p1.unique())
			p2 = p1;
		if (p1.unique())
			;
	}
	// Memory leak
	void TestCircularReference() {
		struct Node
		{
			Node(std::string name) { this->name = name; }
			~Node() { std::cout << "Node " << name.c_str() << "'s dtor" << std::endl; }
			std::shared_ptr<Node> prev;
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
		TestCopy();
		TestDeleter();
		TestSwap();
		TestUnique();
		TestCircularReference();
	}
};
