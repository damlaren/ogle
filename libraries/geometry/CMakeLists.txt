cmake_minimum_required(VERSION 3.3)

set(INC_LIST
  includes/geometry/buffer.h
  includes/geometry/mesh.h
  includes/geometry/ogle_geometry.h
  includes/geometry/transform_matrix.h
)
add_custom_target(ogle_geometry_headers SOURCES ${INC_LIST})

set(SRC_LIST
  sources/mesh.cc
  sources/transform_matrix.cc
)
add_library(ogle_geometry "${SRC_LIST}")
target_link_libraries(ogle_geometry ogle_math)
target_include_directories(ogle_geometry PUBLIC includes)
