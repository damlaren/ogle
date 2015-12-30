cmake_minimum_required(VERSION 3.3)

set(INC_LIST
  includes/application/application.h
  includes/application/glfw_application.h
  includes/application/ogle_application.h
)
add_custom_target(ogle_application_headers SOURCES ${INC_LIST})

set(SRC_LIST
  sources/application.cc
  sources/glfw_application.cc
)
add_library(ogle_application "${SRC_LIST}")
target_link_libraries (ogle_application ogle_renderer)

add_definitions(-DGLEW_STATIC)
target_link_libraries (ogle_application glfw ${GLFW_LIBRARIES}
  glew glu32 opengl32)

target_include_directories(ogle_application PRIVATE
  ${PROJECT_SOURCE_DIR}/3rdparty/easyloggingpp/src
  ${PROJECT_SOURCE_DIR}/3rdparty/glew-1.13.0/include
  ${PROJECT_SOURCE_DIR}/3rdparty/glfw/include)
target_include_directories(ogle_application PUBLIC includes)
