project(dicomifier)
cmake_minimum_required(VERSION 2.6.0)

option(BUILD_EXAMPLES "Build the examples directory." ON)
set(DEFAULT_JS_PATH "${CMAKE_INSTALL_PREFIX}/share/dicomifier" CACHE STRING "Default path of the Javascript files")
set(EXTRA_BUNDLE_DIRS "" CACHE STRING "Extra search path when creating bundle")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}" ${CMAKE_MODULE_PATH})

include(CTest)

add_subdirectory(src)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

add_subdirectory(configuration)
