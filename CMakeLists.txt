cmake_minimum_required(VERSION 2.8.4)
project(concurrent_queue)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

add_executable(interrupt examples/interrupt.cpp)
add_executable(producer_consumer examples/producer_consumer.cpp)
add_executable(wait_pop examples/wait_pop.cpp)
