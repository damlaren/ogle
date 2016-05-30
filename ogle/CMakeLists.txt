cmake_minimum_required(VERSION 3.3)

# List of all include files. Add a custom target so they're
# visible in IDEs.
set(
  INC_LIST
  includes/application/application.h

  includes/config/configuration.h

  includes/engine/engine.h
  includes/entity/component.h
  includes/entity/entity.h

  includes/file_system/directory.h
  includes/file_system/file_path.h
  includes/file_system/text_file.h
  includes/file_system/yaml_file.h

  includes/geometry/mesh.h
  includes/geometry/mesh_loader.h
  includes/geometry/ray.h
  includes/geometry/transform.h
  includes/geometry/transformation_matrix.h

  includes/input/glfw_keyboard_input.h
  includes/input/keyboard_input.h

  includes/math/angle.h
  includes/math/fp_comparison.h
  includes/math/matrix.h
  includes/math/quaternion.h
  includes/math/vector.h

  includes/memory/buffer.h
  includes/memory/ogle_memory.h

  includes/ogle/ogle.h

  includes/renderer/buffered_mesh.h
  includes/renderer/camera.h
  includes/renderer/glfw_buffered_mesh.h
  includes/renderer/glfw_mesh_renderer.h
  includes/renderer/glfw_window.h
  includes/renderer/glsl_shader.h
  includes/renderer/mesh_renderer.h
  includes/renderer/opengl_primitive_types.h
  includes/renderer/perspective_camera.h
  includes/renderer/renderer.h
  includes/renderer/scene_graph.h
  includes/renderer/scene_renderer.h
  includes/renderer/shader.h
  includes/renderer/window.h
  includes/resource/resource.h
  includes/resource/resource_manager.h
  includes/resource/resource_metadata.h

  includes/std/containers.h
  includes/std/custom_allocator.h
  includes/std/default_allocator.h
  includes/std/new_wrappers.h

  includes/util/string_utils.h
)
add_custom_target(ogle_headers SOURCES ${INC_LIST})

# List of all source files.
set(
  SRC_LIST
  sources/application/application.cc

  sources/config/configuration.cc

  sources/engine/engine.cc

  sources/entity/component.cc
  sources/entity/entity.cc

  sources/file_system/directory.cc
  sources/file_system/file_path.cc
  sources/file_system/text_file.cc
  sources/file_system/yaml_file.cc

  sources/geometry/mesh.cc
  sources/geometry/mesh_loader.cc
  sources/geometry/transform.cc
  sources/geometry/transformation_matrix.cc

  sources/input/glfw_keyboard_input.cc
  sources/input/keyboard_input.cc

  sources/math/angle.cc

  sources/memory/buffer.cc

  sources/renderer/buffered_mesh.cc
  sources/renderer/glfw_buffered_mesh.cc
  sources/renderer/glfw_mesh_renderer.cc
  sources/renderer/glfw_window.cc
  sources/renderer/glsl_shader.cc
  sources/renderer/mesh_renderer.cc
  sources/renderer/opengl_primitive_types.cc
  sources/renderer/perspective_camera.cc
  sources/renderer/renderer.cc
  sources/renderer/scene_graph.cc
  sources/renderer/scene_renderer.cc
  sources/renderer/shader.cc
  sources/renderer/window.cc

  sources/resource/resource.cc
  sources/resource/resource_manager.cc
  sources/resource/resource_metadata.cc

  sources/util/string_utils.cc
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
