#include <iostream>
#include <vector>

class A
{
public:
	A(int i):i_(i){	std::cout << "A ctor" << std::endl;	}
	~A(){}
	int getI() const { return i_; }
private:
	int i_;
};

class B
{
public:
	B(float f) :f_(f) {	std::cout << "B ctor" << std::endl; }
	~B() {}
	//void* operator new(size_t size, void *p)
	//{
	//	return p;
	//}
private:
	float f_;
};

// placement-new for A
void* operator new(size_t size, A* p)
{
	return p;
}

/* duplicate definition
void* operator new(size_t size, void* p)	// placement-new
void* operator new(size_t size)				// new
*/
void main() {
	void* pMemPool = calloc(100, sizeof(A));
	A* pA = new (static_cast<A*>(pMemPool)) A(1); // user-defined placement-new
	pA->~A(); // clear memory

	B* pB = new (pMemPool) B(1.0f);
	pB->~B();

	free(pMemPool);
}