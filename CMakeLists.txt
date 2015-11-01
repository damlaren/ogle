cmake_minimum_required(VERSION 2.8)
project(ogle)

# Require C++14 support. Cutting-edge features!
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

add_subdirectory(ogle)
add_subdirectory(apps)

add_library(ogle ogle/sources/core.cc)
target_link_libraries (ogle ogle_math)
target_include_directories(ogle PUBLIC .)
