cmake_minimum_required(VERSION 3.9)
project(proj2_v2)

set(CMAKE_CXX_STANDARD 11)
include_directories(nvwa dat)

add_executable(proj2_v2 main.cpp bool_array.cpp debug_new.cpp mem_pool_base.cpp static_mem_pool.cpp deklaracje.h definicje.cpp)