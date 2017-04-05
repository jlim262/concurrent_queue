#include <iostream>
#include <thread>
#include "../concurrent_queue.hpp"

#define NUM_OF_THREAD 4
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
    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;

    // consumers will wait until something is available in the queue
    for (int i=0; i<NUM_OF_THREAD; i++)
        consumers.emplace_back(pop_task, &queue, COUNT);

    // producers will put something in the queue
    for (int i=0; i<NUM_OF_THREAD; i++)
        producers.emplace_back(push_task, &queue, COUNT);

    // wait until they finish
    for (std::thread& producer : producers)
        producer.join();
    for (std::thread& consumer : consumers)
        consumer.join();

    // produced count should be same as consumed count
    if (!queue.empty())
        std::cout << "Failed. It should consume all\n";

    std::cout << "Succeeded. Consumed all.\n";
    return 0;
}