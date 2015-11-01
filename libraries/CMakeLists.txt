add_subdirectory(ogle)

add_library(ogle sources/core.cc)
target_link_libraries (ogle ogle_math ogle_window)
target_include_directories(ogle PUBLIC .)