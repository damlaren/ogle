cmake_minimum_required(VERSION 2.8)
project(Ogle)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

# Require C++14 support. Cutting-edge features!
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
set_property(GLOBAL PROPERTY CXX_STANDARD_REQUIRED ON)
