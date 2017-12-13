cmake_minimum_required(VERSION 3.9)
project(nvwa)

set(CMAKE_CXX_STANDARD 11)

add_executable(nvwa
    _nvwa.h
    bool_array.cpp
    bool_array.h
    c++11.h
    class_level_lock.h
    cont_ptr_utils.h
    debug_new.cpp
    debug_new.h
    fast_mutex.h
    fc_queue.h
    fixed_mem_pool.h
    mem_pool_base.cpp
    mem_pool_base.h
    object_level_lock.h
    pctimer.h
    set_assign.h
    static_assert.h
    static_mem_pool.cpp
    static_mem_pool.h
    type_traits.h)
