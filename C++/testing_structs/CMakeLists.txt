cmake_minimum_required(VERSION 3.9)
project(testing_structs)
include_directories(nvwa)

set(CMAKE_CXX_STANDARD 11)

add_executable(testing_structs
        bool_array.cpp
        debug_new.cpp
        mem_pool_base.cpp
        static_mem_pool.cpp
        main.cpp)
