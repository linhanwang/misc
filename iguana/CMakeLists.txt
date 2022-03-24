cmake_minimum_required(VERSION 3.20)
project(misc)

set(CMAKE_CXX_STANDARD 20)

add_executable(macro main.cpp)
add_executable(mini_iguana mini_iguana.cpp)
add_executable(void_t void_t.cpp)
add_executable(variadic_arg variadic_arg.cpp)