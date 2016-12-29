#pragma once

#include <queue>
#include <atomic>
#include <mutex>
#include <memory>
#include <iostream>
#include <vector>
#include <cstdio>

namespace TestThread {

	bool g_run = true;

	class MathTask {
	public:
		MathTask() = default;
		virtual ~MathTask() = default;
		virtual int exec() = 0;
	};

	class SumTask:public MathTask {
	public:
		SumTask(int a, int b)
			:a_(a),b_(b){}
		int exec() override {
			return a_ + b_;
		}
	private:
		int a_, b_;
	};

	class MulTask:public MathTask {
	public:
		MulTask(int a,int b)
			:a_(a),b_(b){}
		int exec() {
			return a_*b_;
		}
	private:
		int a_, b_;
	};

	typedef std::shared_ptr<MathTask> MathTaskPtr;

	class TaskQueue {
	public:
		TaskQueue() {}
		~TaskQueue() {}

		bool empty() {
			if (q_.size())
				return false;
			else
				return true;
		}

		MathTaskPtr pop() {
			std::lock_guard<std::mutex> l(m_);
			MathTaskPtr t = q_.front();
			q_.pop();
			return t;
		}

		void push(MathTaskPtr t) {
			std::lock_guard<std::mutex> l(m_);
			q_.push(t);
		}
	private:
		std::queue<MathTaskPtr> q_;
		std::mutex m_;
	};

	TaskQueue g_taskQueue;

	void threadFunc() {
		while (g_run) {
			if (g_taskQueue.empty())
				continue;
			MathTaskPtr p = g_taskQueue.pop();
			int result = p->exec();
			//std::cout << "tid: " << std::this_thread::get_id() << " result: " << result << std::endl;
			printf("tid: %d result: %d\n", std::this_thread::get_id(), result);
		}
	}

	void DoTest() {
		for (int i = 0; i < 1000; i++) {
			if (i % 2) {
				g_taskQueue.push(std::make_shared<MulTask>(3, 2));
			}
			else {
				g_taskQueue.push(std::make_shared<SumTask>(3, 2));
			}
		}

		std::vector<std::thread> tvec;
		for (int i = 0; i < 4; i++)
			tvec.emplace_back(threadFunc);

		for (int i = 0; i < 1000; i++) {
			if (i % 2) {
				g_taskQueue.push(std::make_shared<MulTask>(3, 4));
			}
			else {
				g_taskQueue.push(std::make_shared<SumTask>(3, 4));
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
		g_run = false;
		for (auto &t : tvec) {
			t.join();
		}
	}
}