cmake_minimum_required(VERSION 3.30)
project(U8Lab)

set(CMAKE_CXX_STANDARD 20)

add_executable(U8Lab main.cpp
        Hashtable.cpp
        Hashtable.hpp)
