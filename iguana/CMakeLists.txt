cmake_minimum_required(VERSION 3.20)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled main.cpp)
add_executable(mini_iguana mini_iguana.cpp ../blaze/test_blaze.cpp ../blaze/Inline.h ../blaze/simd/SIMDPack.h ../blaze/simd/BasicTypes.h)
add_executable(void_t void_t.cpp)
add_executable(variadic_arg variadic_arg.cpp)