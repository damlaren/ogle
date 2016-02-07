cmake_minimum_required(VERSION 3.3)

set(SRC_LIST
  sources/main.cc
)
add_executable(triangle ${SRC_LIST})

add_definitions(-DGLEW_STATIC)
target_link_libraries(triangle PUBLIC ogle)
target_include_directories(triangle PRIVATE
  ${PROJECT_SOURCE_DIR}/3rdparty/glew-1.13.0/include
  ${PROJECT_SOURCE_DIR}/3rdparty/glfw/include)
