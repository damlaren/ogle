aux_source_directory(sources SRC_LIST)
add_library(ogle_util "${SRC_LIST}")
target_include_directories(ogle_util PUBLIC includes)
