add_definitions("-D HAVE_CONFIG_H")

include_directories(${CMAKE_SOURCE_DIR}/src)

set(examples javascriptvm dump_as_xml dump_as_json)

foreach(example ${examples})
    add_executable(${example} ${example}.cpp)
    target_link_libraries(${example} v8 libdicomifier)
endforeach()
