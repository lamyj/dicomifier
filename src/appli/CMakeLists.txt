find_package(DCMTK REQUIRED)
find_package(Boost COMPONENTS filesystem program_options system regex REQUIRED)
find_package(Qt4 REQUIRED QtGui)
include(${QT_USE_FILE})

add_definitions(-DHAVE_CONFIG_H)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib
                    ${CMAKE_CURRENT_SOURCE_DIR}/../gui
                    ${QT_INCLUDES})

add_executable(bruker2dicom "main_bruker2dicom.cpp")
target_link_libraries(bruker2dicom libdicomifier ${Boost_LIBRARIES})

add_executable(dicomifier "main_dicomifier.cpp")
target_link_libraries(dicomifier libdicomifier
                                 libdicomifiergui
                                 ${QT_LIBRARIES}
                                 ${Boost_LIBRARIES})

install(TARGETS bruker2dicom dicomifier
        RUNTIME DESTINATION bin/
        COMPONENT applications)

# copy all header files to the include directory
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        FILE_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
        DIRECTORY_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
        DESTINATION include/dicomifier/
        FILES_MATCHING PATTERN "*.h")
