cmake_minimum_required(VERSION 3.3)

set(INC_LIST
  includes/config/configuration.h
  includes/config/ogle_config.h
)
add_custom_target(ogle_config_headers SOURCES ${INC_LIST})

set(SRC_LIST
  sources/configuration.cc
)
add_library(ogle_config "${SRC_LIST}")
target_link_libraries(ogle_config PUBLIC yaml-cpp ogle_std)
target_include_directories(ogle_config PRIVATE
  ${PROJECT_SOURCE_DIR}/3rdparty/easyloggingpp/src)
target_include_directories(ogle_config PUBLIC includes)
