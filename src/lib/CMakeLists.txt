find_package(DCMTK REQUIRED)
find_package(Boost COMPONENTS date_time filesystem system regex REQUIRED)

add_definitions(-DBOOST_FILESYSTEM_VERSION=3)
add_definitions(-DHAVE_CONFIG_H)

# add include
include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${Boost_INCLUDE_DIRS}
                    ${Nifti_INCLUDE_DIRS})

# create the library
file(GLOB_RECURSE files "*.cpp")
add_library(libdicomifier SHARED ${files})
set_target_properties(libdicomifier PROPERTIES OUTPUT_NAME dicomifier)
target_link_libraries(libdicomifier dcmtkpp dcmtls ssl dcmdata dcmnet jsoncpp log4cpp niftiio oflog ofstd v8 wrap pthread z ${Boost_LIBRARIES})

# deploy the library
install(TARGETS libdicomifier
        LIBRARY DESTINATION lib
        COMPONENT libraries)

# copy all header files to the include directory
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        FILE_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
        DIRECTORY_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
        DESTINATION include/dicomifier/
        FILES_MATCHING PATTERN "*.h")
