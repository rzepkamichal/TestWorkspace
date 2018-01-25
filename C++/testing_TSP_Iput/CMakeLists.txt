cmake_minimum_required(VERSION 3.9)
project(testing_TSP_Iput)

set(CMAKE_CXX_STANDARD 11)
include_directories(nvwa)
add_executable(testing_TSP_Iput main.cpp bool_array.cpp debug_new.cpp mem_pool_base.cpp static_mem_pool.cpp)