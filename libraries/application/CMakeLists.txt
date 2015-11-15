aux_source_directory(sources SRC_LIST)
add_library(ogle_application "${SRC_LIST}")
target_link_libraries (ogle_application ogle_renderer)
target_include_directories(ogle_application PRIVATE
  ${PROJECT_SOURCE_DIR}/3rdparty/easyloggingpp/src)
target_include_directories(ogle_application PUBLIC includes)
