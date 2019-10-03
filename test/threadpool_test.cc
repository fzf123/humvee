#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

#include "thread_pool/thread_pool.h"

int print_num(int num) {
    std::cout << num << std::endl;
    return 0;
}

int main() {
    humvee::ThreadPool thread_pool;
    thread_pool.init(30);

    for (int i = 0; i < 100; ++i) {
        std::function<int()> task = std::bind(print_num, i);
        thread_pool.schedule(task);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    return 0;
}
