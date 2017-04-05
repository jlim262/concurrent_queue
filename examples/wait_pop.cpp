#include <iostream>
#include <thread>
#include "../concurrent_queue.hpp"

using lime62::concurrent_queue;

int main() {
    auto pop_task = [](concurrent_queue<int>* q) {
        try {
            std::cout << "It waits until something is pushed in the queue.\n";
            int v = q->front();
            q->pop();
            std::cout << "Got a value(" << v << ")\n";
        } catch (std::runtime_error re) {
            std::cout << re.what() << std::endl;
        }
    };

    concurrent_queue<int> queue;
    std::thread t(pop_task, &queue);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "Pushed a value in the queue.\n";
    queue.push(1);
    t.join();
    return 0;
}