find_package(DCMTK REQUIRED)

add_definitions(-DHAVE_CONFIG_H)
file(GLOB_RECURSE files "*.cpp")
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(librouter SHARED ${files})
set_target_properties(librouter PROPERTIES OUTPUT_NAME router)
target_link_libraries(librouter dcmdata oflog ofstd pthread z)
