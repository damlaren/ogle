cmake_minimum_required(VERSION 3.3)

set(INC_LIST
  includes/input/glfw_keyboard_input.h
  includes/input/keyboard_input.h
  includes/input/ogle_input.h
)
add_custom_target(ogle_input_headers SOURCES ${INC_LIST})

set(SRC_LIST
  sources/glfw_keyboard_input.cc
  sources/keyboard_input.cc
)
add_library(ogle_input "${SRC_LIST}")
target_link_libraries(ogle_input
  ogle_config ogle_renderer ogle_std
  glfw ${GLFW_LIBRARIES} glew glu32 opengl32)

target_include_directories(ogle_input PRIVATE
  ${PROJECT_SOURCE_DIR}/3rdparty/easyloggingpp/src
  ${PROJECT_SOURCE_DIR}/3rdparty/glew-1.13.0/include
  ${PROJECT_SOURCE_DIR}/3rdparty/glfw/include)
target_include_directories(ogle_input PUBLIC includes)
