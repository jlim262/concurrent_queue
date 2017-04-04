cmake_minimum_required(VERSION 2.8.4)
project(concurrent_queue)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Boost REQUIRED COMPONENTS thread system)
include_directories(${Boost_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp)
add_executable(concurrent_queue ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(concurrent_queue ${Boost_LIBRARIES})