#pragma once

#include <atomic>
#include <functional>
#include <thread>

#include "queue/sync_queue.hpp"

namespace humvee {

class ThreadPool {
public:
    typedef std::function<int()> Task;
    typedef std::vector<SyncQueue<Task>*> Pool;

    ThreadPool();
    ~ThreadPool();

    int init(int pool_size);
    int schedule(Task& task);

private:
    void worker(uint32_t queue_index);

    Pool _pool;
    std::vector<std::thread> _work_threads;
    std::atomic<uint32_t> _q_pick{0};
    int _pool_size = 0;
};

}
