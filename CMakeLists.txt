cmake_minimum_required(VERSION 3.16)
project(WinSudo)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-mwindows")
set(SOURCES main.cpp)
add_executable(sudo ${SOURCES})