cmake_minimum_required(VERSION 3.3)

# List of all include files. Add a custom target so they're
# visible in IDEs.
file(
  GLOB
  INC_LIST
  "includes/*/*.h"
  "includes/std/ogle_std.inc"
)
add_custom_target(ogle_headers SOURCES ${INC_LIST})

# List of all source files.
file(
  GLOB
  SRC_LIST
  "sources/*/*.cc"
)

# Create ogle library and link 3rd-party dependencies.
add_library(ogle ${SRC_LIST})
add_definitions(-DGLEW_STATIC)
target_link_libraries(
  ogle
  PRIVATE
  glfw
  ${GLFW_LIBRARIES}
  glew
  glu32
  opengl32
  yaml-cpp
)

# Expose include directories.
target_include_directories(
  ogle
  PUBLIC
  includes
  ${PROJECT_SOURCE_DIR}/3rdparty/easyloggingpp/src
  PRIVATE
  ${PROJECT_SOURCE_DIR}/3rdparty/glew-1.13.0/include
  ${PROJECT_SOURCE_DIR}/3rdparty/glfw/include
  ${PROJECT_SOURCE_DIR}/3rdparty/tinydir
  ${PROJECT_SOURCE_DIR}/3rdparty/yaml-cpp/include
)
