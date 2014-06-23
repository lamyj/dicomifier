find_package(DCMTK REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)

add_definitions(-DHAVE_CONFIG_H)

file(GLOB_RECURSE tests *.cpp)
foreach(test_file ${tests})
    get_filename_component(test ${test_file} NAME_WE)
    add_executable(${test} ${test_file})
    target_link_libraries(${test} librouter)
endforeach()
