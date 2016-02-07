cmake_minimum_required(VERSION 3.3)

set(INC_LIST
  includes/geometry/buffer.h
  includes/geometry/mesh.h
  includes/geometry/ogle_geometry.h
  includes/geometry/ray.h
  includes/geometry/transform.h
  includes/geometry/transformation_matrix.h
)
add_custom_target(ogle_geometry_headers SOURCES ${INC_LIST})

set(SRC_LIST
  sources/mesh.cc
  sources/transform.cc
  sources/transformation_matrix.cc
)
add_library(ogle_geometry "${SRC_LIST}")
target_link_libraries(ogle_geometry ogle_math ogle_util)
target_include_directories(ogle_geometry PRIVATE
  ${PROJECT_SOURCE_DIR}/3rdparty/easyloggingpp/src)
target_include_directories(ogle_geometry PUBLIC includes)
