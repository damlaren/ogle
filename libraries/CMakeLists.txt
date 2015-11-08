add_subdirectory(ogle)

add_library(ogle sources/core.cc)
target_link_libraries(ogle ogle_application ogle_math ogle_util)
target_include_directories(ogle PUBLIC .)
