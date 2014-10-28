find_package(Qt5Widgets REQUIRED)

add_definitions(-DBOOST_FILESYSTEM_VERSION=3)
add_definitions(-DHAVE_CONFIG_H)

file(GLOB_RECURSE files "*.cpp")
file(GLOB_RECURSE files_HEADERS "*.h")
file(GLOB_RECURSE files_FORMS "*.ui")
file(GLOB_RECURSE files_RESOURCES "*.qrc")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${Boost_INCLUDE_DIRS}
                    ${QT_INCLUDES}
                    ${CMAKE_CURRENT_BINARY_DIR})

QT5_WRAP_CPP(files_HEADERS_MOC ${files_HEADERS})
QT5_WRAP_UI(files_FORMS_HEADERS ${files_FORMS})
QT5_ADD_RESOURCES(files_RESOURCES_RCC ${files_RESOURCES})

add_library(libdicomifierihm SHARED ${files}
                                    ${files_HEADERS_MOC}
                                    ${files_FORMS_HEADERS}
                                    ${files_RESOURCES_RCC})
set_target_properties(libdicomifierihm PROPERTIES OUTPUT_NAME dicomifier)

target_link_libraries(libdicomifierihm oflog ofstd wrap pthread z
                                       ${QT_LIBRARIES}
                                       ${Boost_LIBRARIES})
qt5_use_modules(libdicomifierihm Widgets)
