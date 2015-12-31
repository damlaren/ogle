cmake_minimum_required(VERSION 3.3)

set(INC_LIST
  includes/entity/entity.h
  includes/entity/ogle_entity.h
)
add_custom_target(ogle_entity_headers SOURCES ${INC_LIST})

set(SRC_LIST
  sources/entity.cc
)
add_library(ogle_entity "${SRC_LIST}")
target_link_libraries(ogle_entity ogle_renderer)
target_include_directories(ogle_entity PUBLIC includes)
