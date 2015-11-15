aux_source_directory(sources SRC_LIST)
add_executable(triangle ${SRC_LIST})

add_definitions(-DGLEW_STATIC)
target_link_libraries(triangle PUBLIC ogle glfw ${GLFW_LIBRARIES}
  glew glu32 opengl32)
target_include_directories(triangle PRIVATE
  ${PROJECT_SOURCE_DIR}/3rdparty/glew-1.13.0/include
  ${PROJECT_SOURCE_DIR}/3rdparty/glfw/include)
