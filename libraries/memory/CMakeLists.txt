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
target_link_libraries(ogle_memory PUBLIC ogle_std)
target_include_directories(ogle_memory PRIVATE
  ${PROJECT_SOURCE_DIR}/3rdparty/easyloggingpp/src)
target_include_directories(ogle_memory PUBLIC includes)
