find_package(DCMTK REQUIRED)
find_package(Boost COMPONENTS filesystem system regex REQUIRED)

add_executable(dicomifier "main.cpp")
target_link_libraries(dicomifier librouter ${Boost_LIBRARIES})
