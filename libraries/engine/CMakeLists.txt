cmake_minimum_required(VERSION 3.3)

set(INC_LIST
  includes/engine/engine.h
  includes/engine/ogle_engine.h
)
add_custom_target(ogle_engine_headers SOURCES ${INC_LIST})

set(SRC_LIST
  sources/engine.cc
)
add_library(ogle_engine "${SRC_LIST}")
target_link_libraries(ogle_engine
  ogle_config
  ogle_file_system
  ogle_input
  ogle_renderer
  ogle_resource
  ogle_std
)
target_include_directories(ogle_engine PRIVATE
  ${PROJECT_SOURCE_DIR}/3rdparty/easyloggingpp/src)
target_include_directories(ogle_engine PUBLIC includes)
