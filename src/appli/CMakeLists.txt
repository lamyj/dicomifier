find_package(DCMTK REQUIRED)
find_package(Boost COMPONENTS filesystem system regex REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib)

add_executable(dicomifier "main.cpp")
target_link_libraries(dicomifier librouter ${Boost_LIBRARIES})
