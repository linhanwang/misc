cmake_minimum_required(VERSION 3.20)
project(misc)

set(CMAKE_CXX_STANDARD 20)

include_directories(${PROJECT_SOURCE_DIR})

add_compile_options("-march=broadwell")
add_compile_options("-fno-omit-frame-pointer")

add_subdirectory(iguana)
add_subdirectory(blaze)