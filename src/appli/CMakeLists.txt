find_package(DCMTK REQUIRED)
find_package(Boost COMPONENTS filesystem system regex REQUIRED)
find_package(Qt5Widgets REQUIRED)

add_definitions(-DHAVE_CONFIG_H)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib
                    ${CMAKE_CURRENT_SOURCE_DIR}/../ihm
                    ${QT_INCLUDES})

add_executable(dicomifier "main.cpp")
target_link_libraries(dicomifier libdicomifier ${Boost_LIBRARIES})

add_executable(dicomifier_ihm "main_ihm.cpp")
target_link_libraries(dicomifier_ihm libdicomifier libdicomifierihm ${QT_LIBRARIES} ${Boost_LIBRARIES})
qt5_use_modules(dicomifier_ihm Widgets)
