aux_source_directory(sources SRC_LIST)
add_executable(playground ${SRC_LIST})
target_link_libraries(playground LINK_PUBLIC ogle)
