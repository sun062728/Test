class B {
public:
	B():b_(0) {}
	virtual void vfb() { }
	virtual ~B() {}
	void fb() {}
private:
	int b_;
};

class C:public B {
public:
	virtual ~C() {}
	virtual void vfb() override {  }
	virtual void vfc() {  }
	void fc() {}
private:
	int c_;
};

class D :public C {
public:
	virtual ~D() {}
	virtual void vfc() override {  };
	void fd() {};
private:
	int d_;
};