cmake_minimum_required(VERSION 3.3)

set(SRC_LIST
  sources/main.cc
)
add_executable(mesh_viewer ${SRC_LIST})

target_link_libraries(mesh_viewer PUBLIC ogle)
