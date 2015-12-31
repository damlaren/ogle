cmake_minimum_required(VERSION 3.3)

set(SRC_LIST
  sources/main.cc
)
add_executable(triangle ${SRC_LIST})

add_definitions(-DGLEW_STATIC)
target_link_libraries(triangle PUBLIC ogle glfw ${GLFW_LIBRARIES}
  glew glu32 opengl32)
target_include_directories(triangle PRIVATE
  ${PROJECT_SOURCE_DIR}/3rdparty/glew-1.13.0/include
  ${PROJECT_SOURCE_DIR}/3rdparty/glfw/include)

# Copy ogle resources folder.
add_custom_command(TARGET triangle PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:triangle>/resources)
