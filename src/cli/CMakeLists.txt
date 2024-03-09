set(tools "dicomifier")
foreach(tool ${tools})
    configure_file(${tool} ${tool})
    install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/${tool} DESTINATION bin)
endforeach()

file(GLOB_RECURSE files "*")
add_custom_target(
    Scripts ${CMAKE_COMMAND} -E echo "Scripts" SOURCES ${files})
