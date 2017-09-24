cmake_minimum_required(VERSION 3.8)

project(Server)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Server.cpp Server.h)

add_executable(Server ${SOURCE_FILES})