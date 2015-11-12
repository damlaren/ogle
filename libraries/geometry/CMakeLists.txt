aux_source_directory(sources SRC_LIST)
add_library(ogle_geometry "${SRC_LIST}")
target_link_libraries(ogle_geometry ogle_math)
target_include_directories(ogle_geometry PUBLIC includes)
