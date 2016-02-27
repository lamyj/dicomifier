find_package(Boost COMPONENTS filesystem regex system REQUIRED)
find_package(Odil REQUIRED)
find_package(Qt4 REQUIRED QtCore QtGui)

include(${QT_USE_FILE})

file(GLOB_RECURSE files "*.cpp")
file(GLOB_RECURSE headers "*.h")
file(GLOB_RECURSE forms "*.ui")
file(GLOB_RECURSE resources "*.qrc")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../lib
    ${Boost_INCLUDE_DIRS} ${Odil_INCLUDE_DIRS} ${QT_INCLUDES}
    ${CMAKE_CURRENT_BINARY_DIR})
add_definitions(
    -DBOOST_FILESYSTEM_VERSION=3)
link_directories(
    ${Boost_LIBRARY_DIRS})

QT4_WRAP_CPP(mocs ${headers})
QT4_WRAP_UI(compiled_forms ${forms})
QT4_ADD_RESOURCES(compiled_resources ${resources})

add_library(
    libdicomifiergui SHARED
    ${files} ${mocs} ${compiled_forms} ${compiled_resources})

target_link_libraries(
    libdicomifiergui
    libdicomifier ${Boost_LIBRARIES} ${DCMTK_LIBRARIES} ${QT_LIBRARIES})
set_target_properties(libdicomifiergui PROPERTIES OUTPUT_NAME dicomifiergui)

install(
    FILES ${headers} DESTINATION include/dicomifier)
install(
    TARGETS libdicomifiergui
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)
