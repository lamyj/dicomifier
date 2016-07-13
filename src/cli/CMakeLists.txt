install(
    FILES bruker2dicom dicom2nifti
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
    PERMISSIONS 
        OWNER_READ OWNER_EXECUTE 
        GROUP_READ GROUP_EXECUTE 
        WORLD_READ WORLD_EXECUTE
)

file(GLOB_RECURSE files "*")
add_custom_target(
    Scripts ${CMAKE_COMMAND} -E echo "Scripts" SOURCES ${files})
