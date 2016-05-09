cmake_minimum_required(VERSION 3.3)

set(INC_LIST
  includes/file_system/directory.h
  includes/file_system/file_path.h
  includes/file_system/ogle_file_system.h
  includes/file_system/text_file.h
)
add_custom_target(ogle_file_system_headers SOURCES ${INC_LIST})

set(SRC_LIST
  sources/directory.cc
  sources/file_path.cc
  sources/text_file.cc
)
add_library(ogle_file_system "${SRC_LIST}")
target_link_libraries(ogle_file_system PUBLIC ogle_std)
target_include_directories(ogle_file_system PRIVATE
  ${PROJECT_SOURCE_DIR}/3rdparty/easyloggingpp/src
  ${PROJECT_SOURCE_DIR}/3rdparty/tinydir
)
target_include_directories(ogle_file_system PUBLIC includes)
