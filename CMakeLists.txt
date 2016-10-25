project(dicomifier)
set(dicomifier_MAJOR_VERSION 0)
set(dicomifier_MINOR_VERSION 10)
set(dicomifier_PATCH_VERSION 3)
set(dicomifier_VERSION
    ${dicomifier_MAJOR_VERSION}.${dicomifier_MINOR_VERSION}.${dicomifier_PATCH_VERSION})

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
