project(dicomifier)
cmake_minimum_required(VERSION 2.6.0)

option(BUILD_EXAMPLES "Build the examples directory." ON)

include(CTest)

add_subdirectory(src)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

add_subdirectory(configuration)
