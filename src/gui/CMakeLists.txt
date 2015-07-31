find_package(Qt4 REQUIRED QtGui)
include(${QT_USE_FILE})

add_definitions(-DBOOST_FILESYSTEM_VERSION=3)
add_definitions(-DHAVE_CONFIG_H)

file(GLOB_RECURSE files "*.cpp")
file(GLOB_RECURSE files_HEADERS "*.h")
file(GLOB_RECURSE files_FORMS "*.ui")
file(GLOB_RECURSE files_RESOURCES "*.qrc")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_CURRENT_SOURCE_DIR}/../lib
                    ${Boost_INCLUDE_DIRS}
                    ${QT_INCLUDES}
                    ${CMAKE_CURRENT_BINARY_DIR})

QT4_WRAP_CPP(files_HEADERS_MOC ${files_HEADERS})
QT4_WRAP_UI(files_FORMS_HEADERS ${files_FORMS})
QT4_ADD_RESOURCES(files_RESOURCES_RCC ${files_RESOURCES})

add_library(libdicomifiergui SHARED ${files}
                                    ${files_HEADERS_MOC}
                                    ${files_FORMS_HEADERS}
                                    ${files_RESOURCES_RCC})
set_target_properties(libdicomifiergui PROPERTIES OUTPUT_NAME dicomifiergui)

target_link_libraries(libdicomifiergui libdicomifier oflog ofstd wrap pthread z
                                       ${QT_LIBRARIES}
                                       ${Boost_LIBRARIES})

install(TARGETS libdicomifiergui
        LIBRARY DESTINATION lib
        COMPONENT libraries)

# copy all header files to the include directory
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        FILE_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
        DIRECTORY_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
        DESTINATION include/dicomifier/
        FILES_MATCHING PATTERN "*.h")
