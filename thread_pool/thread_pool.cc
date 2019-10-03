#include "thread_pool.h"

namespace humvee {

ThreadPool::ThreadPool() {
}

ThreadPool::~ThreadPool() {
    for (size_t i = 0; i < _pool.size(); ++i) {
        if (_pool[i] != nullptr) {
            delete _pool[i];
        }
    }
    _pool.clear();
}

void ThreadPool::worker(uint32_t queue_index) {
    while (true) {
        bool task_sched = false;
        Task task = nullptr;
        if (_pool[queue_index]->pop(task, true) && task != nullptr) {
            task();
            task_sched = true;
        } else {
            for (int i = 0; i < _pool_size; ++i) {
                // steal
                if (_pool[i]->pop(task, true) && task != nullptr) {
                    task();
                    task_sched = true;
                    break;
                }
            }
        }
        if (!task_sched) {
            sched_yield();
        }
    }
}

int ThreadPool::init(int pool_size) {
    _pool_size = pool_size;
    for (int i = 0; i < _pool_size; ++i) {
        _pool.emplace_back(new SyncQueue<Task>);
    }
    for (int i = 0; i < _pool_size; ++i) {
        std::thread work_thread(&ThreadPool::worker, this, i);
        work_thread.detach();
        _work_threads.emplace_back(std::move(work_thread));
    }
    return 0;
}

int ThreadPool::schedule(Task& task) {
    int queue_index = _q_pick.fetch_add(1) % _pool_size;
    if (!_pool[queue_index]->push(task, true)) {
        return -1;
    }
    return 0;
}

}
