[![Build Status](https://travis-ci.org/lime62/concurrent_queue.svg?branch=master)](https://travis-ci.org/lime62/concurrent_queue)

# A simple C++11 Concurrent Queue based on std::queue.

## Integration

The required source file is `concurrent_queue.hpp`. All you need to do is just including the single file. 
  
```cpp
#include "concurrent_queue.hpp"

// for convenience
using lime62::concurrent_queue;
```

## Usage

`concurrent_queue` provides similar interfaces to `std::queue`. 

### Waits until something is pushed 

```cpp
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
```

## Examples

Execute following script to compile examples. 

```bash
git clone https://github.com/lime62/concurrent_queue.git
cd concurrent_queue
mkdir build
cd build 
cmake ..
make
```