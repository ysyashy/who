cmake_minimum_required(VERSION 3.8)
project(who)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp who.h who.cpp)
add_executable(who ${SOURCE_FILES})