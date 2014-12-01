find_package(DCMTK REQUIRED)
find_package(Boost COMPONENTS filesystem system regex REQUIRED)
find_package(Qt4 REQUIRED QtGui)
include(${QT_USE_FILE})

add_definitions(-DHAVE_CONFIG_H)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib
                    ${CMAKE_CURRENT_SOURCE_DIR}/../ihm
                    ${QT_INCLUDES})

add_executable(dicomifier "main.cpp")
target_link_libraries(dicomifier libdicomifier ${Boost_LIBRARIES})

add_executable(dicomifier_ihm "main_ihm.cpp")
target_link_libraries(dicomifier_ihm libdicomifier
                                     libdicomifierihm
                                     ${QT_LIBRARIES}
                                     ${Boost_LIBRARIES})

install(TARGETS dicomifier dicomifier_ihm
        RUNTIME DESTINATION /usr/bin/
        COMPONENT applications)

# copy all header files to the include directory
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        FILE_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
        DIRECTORY_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
        DESTINATION /usr/include/dicomifier/
        FILES_MATCHING PATTERN "*.h")
