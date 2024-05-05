cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(HEADER_DIR "${CMAKE_SOURCE_DIR}/include")
set(EXTERN_DIR "${CMAKE_SOURCE_DIR}/3rdparty")

project(Plotter)

add_subdirectory(src/Function)
add_subdirectory(src/GUI)
