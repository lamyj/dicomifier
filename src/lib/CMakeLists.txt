find_package(DCMTK REQUIRED)
find_package(Boost COMPONENTS filesystem system regex REQUIRED)

add_definitions(-DBOOST_FILESYSTEM_VERSION=2)
add_definitions(-DHAVE_CONFIG_H)

file(GLOB_RECURSE files "*.cpp")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${Boost_INCLUDE_DIRS})
add_library(librouter SHARED ${files})
set_target_properties(librouter PROPERTIES OUTPUT_NAME router)
target_link_libraries(librouter dcmdata oflog ofstd pthread z ${Boost_LIBRARIES})
