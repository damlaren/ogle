aux_source_directory(sources SRC_LIST)
add_library(ogle_application "${SRC_LIST}")
add_definitions(-DGLEW_STATIC)

# TODO(damlaren): Multi-platform compatibility.
target_link_libraries (ogle_application glfw ${GLFW_LIBRARIES}
  ${PROJECT_SOURCE_DIR}/3rdparty/glew-1.13.0/lib/Release/x64/glew32s.lib
  glu32 opengl32)

target_include_directories(ogle_application PRIVATE
  ${PROJECT_SOURCE_DIR}/3rdparty/easyloggingpp/src
  ${PROJECT_SOURCE_DIR}/3rdparty/glew-1.13.0/include
  ${PROJECT_SOURCE_DIR}/3rdparty/glfw/include)
target_include_directories(ogle_application PUBLIC includes)
