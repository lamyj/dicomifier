# install configuration
file(GLOB_RECURSE scriptjs RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.js")
foreach(HEADER ${scriptjs})
    string(REGEX MATCH "(.*)[/\\]" DIR ${HEADER})
    install(FILES ${HEADER}
            PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
            DESTINATION share/dicomifier/${DIR}
            COMPONENT headers)
endforeach(HEADER ${scriptjs})
