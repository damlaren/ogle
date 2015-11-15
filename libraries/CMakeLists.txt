add_subdirectory(application)
add_subdirectory(geometry)
add_subdirectory(math)
add_subdirectory(renderer)

add_library(ogle sources/ogle.cc)
target_link_libraries(ogle ogle_application ogle_geometry ogle_math ogle_renderer)
target_include_directories(ogle PUBLIC includes
  ${PROJECT_SOURCE_DIR}/3rdparty/easyloggingpp/src)
