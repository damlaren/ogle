aux_source_directory(sources SRC_LIST)
add_executable(triangle ${SRC_LIST})
target_link_libraries(triangle LINK_PUBLIC ogle)
