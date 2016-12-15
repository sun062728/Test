#ifndef ILOVERS_THREAD_POOL_H
#define ILOVERS_THREAD_POOL_H

#include <iostream>
#include <functional>
#include <thread>
#include <condition_variable>
#include <future>
#include <atomic>
#include <vector>
#include <queue>

// �����ռ�
namespace ilovers {
	class TaskExecutor;
}

class ilovers::TaskExecutor {
	using Task = std::function<void()>;
private:
	// �̳߳�
	std::vector<std::thread> pool;
	// �������
	std::queue<Task> tasks;
	// ͬ��
	std::mutex m_task;
	std::condition_variable cv_task;
	// �Ƿ�ر��ύ
	std::atomic<bool> stop;

public:
	// ����
	TaskExecutor(size_t size = 4) : stop{ false } {
		size = size < 1 ? 1 : size;
		for (size_t i = 0; i< size; ++i) {
			pool.emplace_back(&TaskExecutor::schedual, this);    // push_back(std::thread{...})
		}
	}

	// ����
	~TaskExecutor() {
		for (std::thread& thread : pool) {
			thread.detach();    // ���̡߳���������
								//thread.join();        // �ȴ���������� ǰ�᣺�߳�һ����ִ����
		}
	}

	// ֹͣ�����ύ
	void shutdown() {
		this->stop.store(true);
	}

	// ���������ύ
	void restart() {
		this->stop.store(false);
	}

	// �ύһ������
	template<class F, class... Args>
	auto commit(F&& f, Args&&... args) ->std::future<decltype(f(args...))> {
		if (stop.load()) {    // stop == true ??
			throw std::runtime_error("task executor have closed commit.");
		}

		using ResType = decltype(f(args...));    // typename std::result_of<F(Args...)>::type, ���� f �ķ���ֵ����
		auto task = std::make_shared<std::packaged_task<ResType()>>(
			std::bind(std::forward<F>(f), std::forward<Args>(args)...)
			);    // wtf !
		{    // ������񵽶���
			std::lock_guard<std::mutex> lock{ m_task };
			tasks.emplace([task]() {   // push(Task{...})
				(*task)();
			});
		}
		cv_task.notify_all();    // �����߳�ִ��

		std::future<ResType> future = task->get_future();
		return future;
	}

private:
	// ��ȡһ����ִ�е� task
	Task get_one_task() {
		std::unique_lock<std::mutex> lock{ m_task };
		cv_task.wait(lock, [this]() { return !tasks.empty(); });    // wait ֱ���� task
		Task task{ std::move(tasks.front()) };    // ȡһ�� task
		tasks.pop();
		return task;
	}

	// �������
	void schedual() {
		while (true) {
			if (Task task = get_one_task()) {
				task();    //
			}
			else {
				// return;    // done
			}
		}
	}
};

#endif