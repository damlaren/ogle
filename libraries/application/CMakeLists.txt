cmake_minimum_required(VERSION 3.3)

set(INC_LIST
  includes/application/application.h
  includes/application/ogle_application.h
)
add_custom_target(ogle_application_headers SOURCES ${INC_LIST})

set(SRC_LIST
  sources/application.cc
)
add_library(ogle_application "${SRC_LIST}")
target_link_libraries (ogle_application ogle_engine ogle_std)

target_include_directories(ogle_application PRIVATE
  ${PROJECT_SOURCE_DIR}/3rdparty/easyloggingpp/src)
target_include_directories(ogle_application PUBLIC includes)
