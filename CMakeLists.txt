cmake_minimum_required(VERSION 4.1)
project(RK_1)

set(CMAKE_CXX_STANDARD 20)

if(MSVC)
    add_compile_options(/utf-8)
endif()

add_executable(RK_1 main.cpp)
add_executable(variant3_task1 variant3_task1.cpp)
add_executable(variant3_task2 variant3_task2.cpp)

