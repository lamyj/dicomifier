configure_file("bruker2dicom" "${CMAKE_CURRENT_BINARY_DIR}/bruker2dicom")
configure_file("dicom2nifti" "${CMAKE_CURRENT_BINARY_DIR}/dicom2nifti")
install(
    PROGRAMS 
        ${CMAKE_CURRENT_BINARY_DIR}/bruker2dicom 
        ${CMAKE_CURRENT_BINARY_DIR}/dicom2nifti
    DESTINATION bin
)

file(GLOB_RECURSE files "*")
add_custom_target(
    Scripts ${CMAKE_COMMAND} -E echo "Scripts" SOURCES ${files})
