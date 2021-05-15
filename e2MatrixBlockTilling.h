#include <thread>
#include <mutex>
#include <list>
#include <functional>
#include <condition_variable>
using namespace std;

struct data {
	int thread_id;
	int row_0;
	int row_1;
	int columns_0;
	int columns_1;
};

class T {

	bool is_running;
	mutex _mutex;
	thread thr;
	list <function<void()>> f_queue;

public:

	T() : is_running{false} {}
	~T() { stop(); }

	template <typename... Args>
	void push_func(Args&&... args) {
		f_queue.push_back(bind(forward<Args>(args)...));
	}

	void start_func() {
		thr = thread([this] {
			std::scoped_lock<std::mutex> lock(_mutex);
            for (auto& func : f_queue) {
                func();
            }
            return;
		});
	}

	void start() {
		scoped_lock<mutex> lock(_mutex);
		if (is_running) {return;}
		is_running = true;
		start_func();
	}

	void stop() {
		scoped_lock<mutex> lock(_mutex);
		if (is_running == false) {return;}
		is_running = false;
		thr.join();
	}

};