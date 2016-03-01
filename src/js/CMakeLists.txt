# install configuration
file(GLOB_RECURSE scriptjs RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.js")
add_custom_target(
    Javascript ${CMAKE_COMMAND} -E echo "Javascript files" SOURCES ${scriptjs})
foreach(HEADER ${scriptjs})
    string(REGEX MATCH "(.*)[/\\]" DIR ${HEADER})
    install(FILES ${HEADER}
            DESTINATION share/dicomifier/${DIR}
            COMPONENT headers)
endforeach()
