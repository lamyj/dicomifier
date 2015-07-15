project(dicomifier)
cmake_minimum_required(VERSION 2.6.0)

include(CTest)

add_subdirectory(src)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

add_subdirectory(configuration)
