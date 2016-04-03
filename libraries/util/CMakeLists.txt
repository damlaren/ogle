cmake_minimum_required(VERSION 3.3)

set(INC_LIST
  includes/util/blank.h
  includes/util/ogle_util.h
  includes/util/string_utils.h
)
add_custom_target(ogle_util_headers SOURCES ${INC_LIST})

set(SRC_LIST
  sources/blank.cc
  sources/string_utils.cc
)
add_library(ogle_util "${SRC_LIST}")
target_link_libraries(ogle_util PUBLIC ogle_std)
target_include_directories(ogle_util PRIVATE
  ${PROJECT_SOURCE_DIR}/3rdparty/easyloggingpp/src)
target_include_directories(ogle_util PUBLIC includes)
