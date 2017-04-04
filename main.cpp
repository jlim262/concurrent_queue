#include <iostream>
#include <boost/thread/thread.hpp>
#include "src/concurrent_queue.hpp"

using namespace lime62;

int main() {
    auto pop_task = [](concurrent_queue<int> *q, int n) {
        for (int i = 0; i < n; i++) {
            try {
                q->front();
                q->pop();
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
    boost::thread_group producers;
    boost::thread_group consumers;

    for (int i = 0; i < 5; i++) {
        producers.create_thread(boost::bind<void>(push_task, &queue, 100000));
    }
    for (int i = 0; i < 5; i++) {
        consumers.create_thread(boost::bind<void>(pop_task, &queue, 100000));
    }

    producers.join_all();
    consumers.join_all();

    assert(queue.empty());

    return 0;
}