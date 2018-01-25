cmake_minimum_required(VERSION 3.9)
project(training_dynamic_data)

set(CMAKE_CXX_STANDARD 11)

include_directories(memory-leaks)
add_executable(training_dynamic_data main.cpp bool_array.cpp debug_new.cpp mem_pool_base.cpp static_mem_pool.cpp)
