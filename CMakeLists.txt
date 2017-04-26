project(dicomifier)
set(dicomifier_MAJOR_VERSION 0)
set(dicomifier_MINOR_VERSION 10)
set(dicomifier_PATCH_VERSION 6)
set(dicomifier_VERSION
    ${dicomifier_MAJOR_VERSION}.${dicomifier_MINOR_VERSION}.${dicomifier_PATCH_VERSION})

cmake_minimum_required(VERSION 2.8)

option(BUILD_EXAMPLES "Build the examples directory." ON)
option(BUILD_GUI "Build the graphical user interface" OFF)
set(EXTRA_BUNDLE_DIRS "" CACHE STRING "Extra search path when creating bundle")

# Add the C++0x or C++11 flag
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG(-std=c++11 COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG(-std=c++0x COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif()

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}" ${CMAKE_MODULE_PATH})

include(CTest)

add_subdirectory(src)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
