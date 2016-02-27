find_package(Boost COMPONENTS filesystem program_options system REQUIRED)
find_package(Odil REQUIRED)
find_package(Qt4 REQUIRED QtCore QtGui)

include(${QT_USE_FILE})

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib ${CMAKE_CURRENT_SOURCE_DIR}/../gui
    ${Boost_INCLUDE_DIRS} ${Odil_INCLUDE_DIRS} ${QT_INCLUDES})
add_definitions(
    -DBOOST_FILESYSTEM_VERSION=3)
link_directories(
    ${Boost_LIBRARY_DIRS})

add_executable(bruker2dicom "bruker2dicom.cpp")
target_link_libraries(
    bruker2dicom libdicomifier ${Boost_LIBRARIES} ${Odil_LIBRARIES})

add_executable(dicom2nifti "dicom2nifti.cpp")
target_link_libraries(dicom2nifti libdicomifier ${Boost_LIBRARIES})

add_executable(dicomifier "dicomifier.cpp")
target_link_libraries(
    dicomifier
    libdicomifier libdicomifiergui ${Boost_LIBRARIES} ${QT_LIBRARIES})

install(
    TARGETS bruker2dicom dicom2nifti dicomifier
    RUNTIME DESTINATION bin)
