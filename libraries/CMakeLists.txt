cmake_minimum_required(VERSION 3.3)

set(INC_LIST
  includes/ogle/ogle.h
)
add_custom_target(ogle_headers SOURCES ${INC_LIST})

set(SRC_LIST
  sources/ogle.cc
)

add_subdirectory(application)
add_subdirectory(entity)
add_subdirectory(geometry)
add_subdirectory(math)
add_subdirectory(renderer)
add_subdirectory(resource)
add_subdirectory(util)

add_library(ogle sources/ogle.cc)
target_link_libraries(ogle
  ogle_application
  ogle_entity
  ogle_geometry
  ogle_math
  ogle_renderer
  ogle_resource
  ogle_util
)
target_include_directories(ogle PUBLIC includes
  ${PROJECT_SOURCE_DIR}/3rdparty/easyloggingpp/src)
