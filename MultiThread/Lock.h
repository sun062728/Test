#pragma once
#include <atomic>

class SpinLock
{
public:
	SpinLock() { /*memset(&l, 0, sizeof(l));*/ }
	SpinLock(const SpinLock &) = delete;
	SpinLock(SpinLock &&) = delete;
	SpinLock operator=(const SpinLock &l) = delete;
	~SpinLock() {}

	inline void Lock() {
		while (l.test_and_set(std::memory_order_acquire))
			;
	}
	inline void Unlock() { l.clear(std::memory_order_release); }
private:
	std::atomic_flag l = ATOMIC_FLAG_INIT;
};