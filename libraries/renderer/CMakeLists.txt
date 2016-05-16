cmake_minimum_required(VERSION 3.3)

set(INC_LIST
  includes/renderer/buffered_mesh.h
  includes/renderer/camera.h
  includes/renderer/glfw_buffered_mesh.h
  includes/renderer/glfw_mesh_renderer.h
  includes/renderer/glfw_window.h
  includes/renderer/glsl_shader.h
  includes/renderer/mesh_renderer.h
  includes/renderer/ogle_renderer.h
  includes/renderer/perspective_camera.h
  includes/renderer/renderer.h
  includes/renderer/scene_graph.h
  includes/renderer/scene_renderer.h
  includes/renderer/shader.h
  includes/renderer/window.h
)
add_custom_target(ogle_renderer_headers SOURCES ${INC_LIST})

set(SRC_LIST
  sources/buffered_mesh.cc
  sources/glfw_buffered_mesh.cc
  sources/glfw_mesh_renderer.cc
  sources/glfw_window.cc
  sources/glsl_shader.cc
  sources/mesh_renderer.cc
  sources/perspective_camera.cc
  sources/renderer.cc
  sources/scene_graph.cc
  sources/scene_renderer.cc
  sources/shader.cc
  sources/window.cc
)
add_library(ogle_renderer "${SRC_LIST}")

add_definitions(-DGLEW_STATIC)
target_link_libraries (ogle_renderer
  ogle_config
  ogle_entity
  ogle_file_system
  ogle_geometry
  ogle_input
  ogle_math
  ogle_resource
  ogle_util
  ogle_std
  glfw
  ${GLFW_LIBRARIES}
  glew
  glu32
  opengl32
)

target_include_directories(
  ogle_renderer
  PRIVATE
  ${PROJECT_SOURCE_DIR}/3rdparty/easyloggingpp/src
)
target_include_directories(
  ogle_renderer
  PUBLIC
  includes
  ${PROJECT_SOURCE_DIR}/3rdparty/glew-1.13.0/include
  ${PROJECT_SOURCE_DIR}/3rdparty/glfw/include
)
