cmake_minimum_required(VERSION 3.3)

set(INC_LIST
  includes/math/angle.h
  includes/math/fp_comparison.h
  includes/math/matrix.h
  includes/math/ogle_math.h
  includes/math/quaternion.h
  includes/math/vector.h
)
add_custom_target(ogle_math_headers SOURCES ${INC_LIST})

set(SRC_LIST
  sources/angle.cc
)
add_library(ogle_math "${SRC_LIST}")
target_link_libraries(ogle_math PUBLIC ogle_std)
target_include_directories(ogle_math PRIVATE
  ${PROJECT_SOURCE_DIR}/3rdparty/easyloggingpp/src)
target_include_directories(ogle_math PUBLIC includes)
