cmake_minimum_required(VERSION 3.10)

# set the project name
project(passmanpp)

# add the executable
add_executable(passmanpp src/main.cpp)

set(CMAKE_CXX_FLAGS "-lcryptopp")
