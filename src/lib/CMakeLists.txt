find_package(DCMTK REQUIRED)
find_package(Boost COMPONENTS filesystem system regex REQUIRED)

add_definitions(-DBOOST_FILESYSTEM_VERSION=3)
add_definitions(-DHAVE_CONFIG_H)

file(GLOB_RECURSE files "*.cpp")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${Boost_INCLUDE_DIRS})
add_library(libdicomifier SHARED ${files})
set_target_properties(libdicomifier PROPERTIES OUTPUT_NAME dicomifier)
target_link_libraries(libdicomifier dcmdata dcmnet oflog ofstd pthread z ${Boost_LIBRARIES})
