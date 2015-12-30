cmake_minimum_required(VERSION 3.3)

set(INC_LIST
  includes/ogle/ogle.h
)
add_custom_target(ogle_headers SOURCES ${INC_LIST})

set(SRC_LIST
  sources/ogle.cc
)

add_subdirectory(application)
add_subdirectory(geometry)
add_subdirectory(math)
add_subdirectory(renderer)

aux_source_directory(sources SRC_LIST)
add_library(ogle sources/ogle.cc)
target_link_libraries(ogle ogle_application ogle_geometry ogle_math ogle_renderer)
target_include_directories(ogle PUBLIC includes
  ${PROJECT_SOURCE_DIR}/3rdparty/easyloggingpp/src)
