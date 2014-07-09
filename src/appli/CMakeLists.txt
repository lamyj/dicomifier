find_package(DCMTK REQUIRED)
find_package(Boost COMPONENTS filesystem system regex REQUIRED)

add_definitions(-DHAVE_CONFIG_H)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib)

add_executable(dicomifier "main.cpp")
target_link_libraries(dicomifier libdicomifier ${Boost_LIBRARIES})
