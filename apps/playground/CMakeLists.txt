cmake_minimum_required(VERSION 3.3)

set(SRC_LIST
  sources/main.cc
)
add_executable(playground ${SRC_LIST})
target_link_libraries(playground LINK_PUBLIC ogle)
