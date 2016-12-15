#include <thread>		// std::thread
#include <iostream>
#include <atomic>		// std::atomic_flag, std::atomic_xxx
#include <mutex>		// std::mutex, std::lock_guard, std::unique_lock, std::condition_variable
#include <vector>
#include <functional>	// std::funtion, std::binder
#include <memory>		// std::shared_ptr, std::unique_ptr, std::weak_ptr
#include "Lock.h"

const int g_ThreadCount = std::thread::hardware_concurrency();

static std::atomic_int thread_lock = 1;
//static std::atomic_int thread_lock = 1;
std::mutex thread_mutex;
std::atomic_flag flag = ATOMIC_FLAG_INIT;
std::atomic_bool g_Run = 1;
int count = 0;

void main()
{
	std::shared_ptr<int> sharedPtr = std::make_shared<int>(42);
	std::unique_ptr<int> uniquePtr(new int(7));
	auto ptr = uniquePtr.release();
	//std::shared_ptr<int> p2 = new int(32); // need non-explicit initializor shared_ptr<int>(int *p)
}

//int thread(int arg1, float arg2, SpinLock* l)
//{
//	while (1) {
//		if (!g_Run)
//			return 1;
//		{
//			l->Lock();
//			std::cout << "TID: " << std::this_thread::get_id() << std::endl;
//			count++;
//			l->Unlock();
//		}
//	}
//
//	return 0;
//}
//
//void main()
//{
//	using namespace std::placeholders;
//	auto thread_morph = std::bind(thread, _3, _1, _2);
//	
//
//	auto pLock = new SpinLock;
//	memset(pLock, 0, sizeof(SpinLock));
//	std::vector<std::thread> vecThread;
//	for (auto i = 0; i < 8; ++i)
//		//vecThread.emplace_back(std::thread(thread, 1 * i, 2.1f*i, pLock));
//		vecThread.emplace_back(std::thread(thread, 1 * i, 2.1f*i, pLock));
//	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
//	g_Run = 0;
//	for (auto& t : vecThread)
//		t.join();
//	delete pLock;
//	std::cout << "count: " << count << std::endl;
//	std::cout << "main thread exit!" << std::endl;
//
//	return;
//}