cmake_minimum_required(VERSION 3.15)
project(CTemplatedInputValidationTesting)


SET(CMAKE_C_COMPILER clang)
SET(CMAKE_CXX_COMPILER clang++)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -stdlib=libc++")

add_executable(CTemplatedInputValidationTesting main.cpp)