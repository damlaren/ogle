aux_source_directory(sources SRC_LIST)
add_library(ogle_math "${SRC_LIST}")
target_include_directories(ogle_math PUBLIC includes)
