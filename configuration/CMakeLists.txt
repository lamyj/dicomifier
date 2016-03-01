# install configuration
file(GLOB_RECURSE conffile RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.xml")
foreach(HEADER ${conffile})
    string(REGEX MATCH "(.*)[/\\]" DIR ${HEADER})
    install(FILES ${HEADER}
            DESTINATION etc/dicomifier/${DIR}
            COMPONENT headers)
endforeach()
