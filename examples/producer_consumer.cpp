#include <iostream>
#include <thread>
#include "../concurrent_queue.hpp"

#define COUNT 100000

using lime62::concurrent_queue;

int main() {
    auto pop_task = [](concurrent_queue<int> *q, int n) {
        for (int i = 0; i < n; i++) {
            try {
                int v;
                q->front_pop(v);
            } catch (std::runtime_error re) {
                std::cout << re.what() << std::endl;
            }
        }
    };

    auto push_task = [](concurrent_queue<int> *q, int n) {
        for (int i = 0; i < n; i++) {
            q->push(i);
        }
    };

    concurrent_queue<int> queue;
    std::thread producer(push_task, &queue, COUNT);
    std::thread consumer(pop_task, &queue, COUNT);
    producer.join();
    consumer.join();

    if (!queue.empty())
        std::cout << "Failed. It should consume all\n";

    std::cout << "Succeeded. Consumed all.\n";
    return 0;
}