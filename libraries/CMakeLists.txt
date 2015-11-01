add_subdirectory(ogle)

add_library(ogle sources/core.cc)
target_link_libraries (ogle ogle_math)
target_include_directories(ogle PUBLIC .)