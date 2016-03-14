find_package(Boost COMPONENTS date_time filesystem system regex REQUIRED)
find_package(DCMTK REQUIRED)
find_package(JsonCpp REQUIRED)
find_package(Log4Cpp REQUIRED)
find_package(NIfTI REQUIRED)
find_package(Odil REQUIRED)
find_package(V8 REQUIRED)

file(GLOB_RECURSE headers "*.h")
file(GLOB_RECURSE templates "*.txx")
file(GLOB_RECURSE files "*.cpp")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${Boost_INCLUDE_DIRS} ${DCMTK_INCLUDE_DIRS} ${JsonCpp_INCLUDE_DIRS}
    ${Log4Cpp_INCLUDE_DIRS} ${NIfTI_INCLUDE_DIRS} ${Odil_INCLUDE_DIRS}
    ${V8_INCLUDE_DIRS})
add_definitions(
    ${DCMTK_DEFINITIONS} -DBOOST_FILESYSTEM_VERSION=3)
link_directories(
    ${Boost_LIBRARY_DIRS} ${DCMTK_LIBRARY_DIRS})

add_library(
    libdicomifier SHARED ${files} ${headers} ${templates})

target_link_libraries(
    libdicomifier
    ${Boost_LIBRARIES} ${DCMTK_LIBRARIES} ${JsonCpp_LIBRARIES}
    ${Log4Cpp_LIBRARIES} ${NIfTI_LIBRARIES} ${Odil_LIBRARIES} ${V8_LIBRARIES})
if(DEFAULT_JS_PATH)
    set_property(
        SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/javascript/common.cpp
        PROPERTY COMPILE_DEFINITIONS DICOMIFIER_DEFAULT_JS_PATH="${DEFAULT_JS_PATH}"
    )
else()
    message(WARNING "No default Javascript path")
endif()

set_target_properties(
    libdicomifier PROPERTIES OUTPUT_NAME dicomifier)

install(
    FILES ${headers} ${templates} DESTINATION include/dicomifier)
install(
    TARGETS libdicomifier
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)
