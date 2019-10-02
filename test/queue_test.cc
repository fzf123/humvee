#include <iostream>
#include <string>
#include <vector>
#include <thread>

#include "queue/sync_queue.hpp"

void func(::humvee::SyncQueue<std::string>& q, int idx) {
    std::string foo = std::to_string(idx);
    q.push(foo);
}

int main() {
    ::humvee::SyncQueue<std::string> q;
    std::vector<std::thread> thrs;
    for (int i = 0; i < 10; ++i) {
        thrs.emplace_back(func, std::ref(q), i);
    }
    for (auto& t : thrs) {
        t.join();
    }

    std::string val;
    while (q.pop(val, true)) {
        std::cout << val << std::endl;
    }
    return 0;
}
