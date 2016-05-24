cmake_minimum_required(VERSION 3.3)

set(
  INC_LIST
  includes/std/containers.h
  includes/std/custom_allocator.h
  includes/std/default_allocator.h
  includes/std/new_wrappers.h
  includes/std/ogle_std.inc
)
add_custom_target(ogle_std_headers
  SOURCES
  ${INC_LIST}
)

set(
  SRC_LIST
  sources/ogle_std.cc
)
add_library(
  ogle_std
  "${SRC_LIST}"
)

target_include_directories(
  ogle_std
  PUBLIC
  includes
  PRIVATE
  ${PROJECT_SOURCE_DIR}/3rdparty/easyloggingpp/src
)
