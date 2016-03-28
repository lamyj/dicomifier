# install configuration
file(GLOB_RECURSE scriptjs RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.js")
add_custom_target(
    Javascript ${CMAKE_COMMAND} -E echo "Javascript files" SOURCES ${scriptjs})
foreach(script ${scriptjs})
    string(REGEX MATCH "(.*)[/\\]" DIR ${script})
    install(FILES ${script}
            DESTINATION share/dicomifier/${DIR}
            COMPONENT headers)
    if(APPLE)
        install(FILES ${script}
            DESTINATION dicomifier.app/Contents/Resources/js/${DIR})
    endif()
endforeach()
