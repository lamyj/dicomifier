find_package(Boost 1.58 COMPONENTS date_time filesystem system regex REQUIRED)

file(GLOB_RECURSE headers "*.h")
file(GLOB_RECURSE templates "*.txx")
file(GLOB_RECURSE files "*.cpp")

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${Boost_INCLUDE_DIRS})
add_definitions(-DBOOST_FILESYSTEM_VERSION=3 -DBOOST_ALL_DYN_LINK)
link_directories(${Boost_LIBRARY_DIRS})

add_library(libdicomifier ${files} ${headers} ${templates})

target_link_libraries(libdicomifier ${Boost_LIBRARIES})

set_target_properties(
    libdicomifier PROPERTIES 
    OUTPUT_NAME dicomifier
    VERSION ${dicomifier_VERSION}
    SOVERSION ${dicomifier_MAJOR_VERSION})

install(FILES ${headers} ${templates} DESTINATION include/dicomifier)
install(
    TARGETS libdicomifier
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)
