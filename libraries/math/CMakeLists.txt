cmake_minimum_required(VERSION 3.3)

set(INC_LIST
  includes/math/angle.h
  includes/math/ogle_math.h
  includes/math/matrix.h
  includes/math/vector.h
)
add_custom_target(ogle_math_headers SOURCES ${INC_LIST})

set(SRC_LIST
  sources/angle.cc
  sources/math.cc
)
add_library(ogle_math "${SRC_LIST}")
target_include_directories(ogle_math PUBLIC includes)
