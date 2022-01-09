# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

project ("axl")

# Include sub-projects.
add_subdirectory ("axl_core")
add_subdirectory ("axl")
#
add_subdirectory ("axl_settings")
add_subdirectory ("axl_logging")
