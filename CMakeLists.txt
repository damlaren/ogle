cmake_minimum_required(VERSION 3.3)
project(ogle)

# Require C++14 support.
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler-specific flags that can't be easily set in CMake.
if(CMAKE_COMPILER_IS_GNUCC)
  # Disable exceptions and RTTI.
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -fno-rtti")

  # Enable all warnings and treat them as errors.
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall")
endif (CMAKE_COMPILER_IS_GNUCC)

add_subdirectory(3rdparty)
add_subdirectory(libraries)
add_subdirectory(apps)
