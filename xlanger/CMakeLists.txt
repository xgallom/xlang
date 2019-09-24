cmake_minimum_required(VERSION 3.14)
project(xlanger CXX)

add_library(xlanger INTERFACE)

target_include_directories(xlanger INTERFACE include)

install(DIRECTORY include/ TYPE INCLUDE)
