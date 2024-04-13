cmake_minimum_required(VERSION 3.5)
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(SET CMP0074 NEW)
endif()

project(dicomifier)

set(dicomifier_VERSION 2.5.2)
string(REGEX MATCH "^([0-9]+)\\.([0-9]+)\\.([0-9]+)" _ "${dicomifier_VERSION}")
set(dicomifier_MAJOR_VERSION "${CMAKE_MATCH_1}")
set(dicomifier_MINOR_VERSION "${CMAKE_MATCH_2}")
set(dicomifier_PATCH_VERSION "${CMAKE_MATCH_3}")

option(BUILD_SHARED_LIBS "Build Dicomifier with shared libraries." ON)
option(BUILD_EXAMPLES "Build the examples directory." ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}" ${CMAKE_MODULE_PATH})
set(CMAKE_INSTALL_MESSAGE LAZY)

include(CTest)

add_subdirectory(src)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
