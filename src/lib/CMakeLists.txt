find_package(Boost COMPONENTS date_time filesystem system regex REQUIRED)

file(GLOB_RECURSE headers "*.h")
file(GLOB_RECURSE templates "*.txx")
file(GLOB_RECURSE files "*.cpp")
list(SORT header_files)
list(SORT template_files)
list(SORT files)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_definitions(-DBOOST_FILESYSTEM_VERSION=3 -DBOOST_ALL_DYN_LINK)

add_library(libdicomifier ${files} ${headers} ${templates})
target_link_libraries(
    libdicomifier Boost::date_time Boost::filesystem Boost::regex Boost::system)

if(APPLE)
    # WARNING: Boost::regex may add -licudata  -licui18n  -licuu, which cause 
    # problems with macOS/brew
    find_package(ICU REQUIRED COMPONENTS uc)
    get_filename_component(ICU_FOUND_DIRECTORY "${ICU_UC_LIBRARY}" DIRECTORY)
    target_link_libraries(libdicomifier "-L${ICU_FOUND_DIRECTORY}")
endif()

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
