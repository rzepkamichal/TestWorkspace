cmake_minimum_required(VERSION 3.9)
project(proj_v1)

set(CMAKE_CXX_STANDARD 11)
include_directories(nvwa)
add_executable(proj_v1 main.cpp bool_array.cpp debug_new.cpp mem_pool_base.cpp static_mem_pool.cpp deklaracje.h definicje.cpp)