project(dicomifier)
cmake_minimum_required(VERSION 2.6.0)

option(BUILD_EXAMPLES "Build the examples directory." ON)
set(EXTRA_BUNDLE_DIRS "" CACHE STRING "Extra search path when creating bundle")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}" ${CMAKE_MODULE_PATH})

include(CTest)

add_subdirectory(src)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

add_subdirectory(configuration)
