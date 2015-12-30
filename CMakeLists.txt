cmake_minimum_required(VERSION 3.3)
project(ogle)

# Require C++14 support.
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(3rdparty)
add_subdirectory(libraries)
add_subdirectory(apps)
