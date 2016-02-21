cmake_minimum_required(VERSION 3.3)

set(INC_LIST
  includes/memory/buffer.h
  includes/memory/ogle_memory.h
)
add_custom_target(ogle_memory_headers SOURCES ${INC_LIST})

set(SRC_LIST
  sources/buffer.cc
)
add_library(ogle_memory "${SRC_LIST}")
target_include_directories(ogle_memory PUBLIC includes)
