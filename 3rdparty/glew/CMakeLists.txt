cmake_minimum_required(VERSION 3.3)

add_library(glew src/glew.c)
target_include_directories(glew PUBLIC include)
