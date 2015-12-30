cmake_minimum_required(VERSION 3.3)

set(INC_LIST
  includes/renderer/glfw_renderer.h
  includes/renderer/glfw_window.h
  includes/renderer/glsl_shader.h
  includes/renderer/ogle_renderer.h
  includes/renderer/renderer.h
  includes/renderer/shader.h
  includes/renderer/window.h
)
add_custom_target(ogle_renderer_headers SOURCES ${INC_LIST})

set(SRC_LIST
  sources/glfw_renderer.cc
  sources/glfw_window.cc
  sources/glsl_shader.cc
  sources/renderer.cc
  sources/shader.cc
  sources/window.cc
)
add_library(ogle_renderer "${SRC_LIST}")

add_definitions(-DGLEW_STATIC)
target_link_libraries (ogle_renderer ogle_geometry
  glfw ${GLFW_LIBRARIES} glew glu32 opengl32)

target_include_directories(ogle_renderer PRIVATE
  ${PROJECT_SOURCE_DIR}/3rdparty/easyloggingpp/src)
target_include_directories(ogle_renderer PUBLIC includes
  ${PROJECT_SOURCE_DIR}/3rdparty/glew-1.13.0/include
  ${PROJECT_SOURCE_DIR}/3rdparty/glfw/include)
