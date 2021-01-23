cmake_minimum_required(VERSION 3.5)

project(dicomifier)

set(dicomifier_VERSION 2.0.5)
string(REGEX MATCH "^([0-9]+)\\.([0-9]+)\\.([0-9]+)" _ "${dicomifier_VERSION}")
set(dicomifier_MAJOR_VERSION "${CMAKE_MATCH_1}")
set(dicomifier_MINOR_VERSION "${CMAKE_MATCH_2}")
set(dicomifier_PATCH_VERSION "${CMAKE_MATCH_3}")

option(BUILD_SHARED_LIBS "Build Dicomifier with shared libraries." ON)
option(BUILD_EXAMPLES "Build the examples directory." ON)

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
set(CMAKE_INSTALL_MESSAGE LAZY)

include(CTest)

add_subdirectory(src)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
