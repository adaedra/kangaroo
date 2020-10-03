cmake_minimum_required(VERSION 3.4)
project(kangaroo)

set(CMAKE_CXX_STANDARD 17)
include_directories(${kangaroo_SOURCE_DIR}/include)

add_subdirectory(src bin)
