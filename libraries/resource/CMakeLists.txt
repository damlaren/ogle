cmake_minimum_required(VERSION 3.3)

set(INC_LIST
  includes/resource/resource.h
  includes/resource/resource_manager.h
  includes/resource/resource_metadata.h
  includes/resource/ogle_resource.h
)
add_custom_target(ogle_resource_headers SOURCES ${INC_LIST})

set(SRC_LIST
  sources/resource_manager.cc
  sources/resource_metadata.cc
)
add_library(ogle_resource "${SRC_LIST}")
target_link_libraries(ogle_resource PUBLIC yaml-cpp ogle_file_system ogle_std)
target_include_directories(ogle_resource PRIVATE
  ${PROJECT_SOURCE_DIR}/3rdparty/easyloggingpp/src)
target_include_directories(ogle_resource PUBLIC includes)
