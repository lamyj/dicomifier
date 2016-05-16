find_package(Boost REQUIRED COMPONENTS python)
find_package(JsonCpp REQUIRED)
find_package(PythonLibs 2.7 REQUIRED)

include_directories(
    ${CMAKE_SOURCE_DIR}/src/lib ${Boost_INCLUDE_DIRS}
    ${JsonCpp_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

file(GLOB files "*.cpp")
python_add_module(pydicomifier_bruker SHARED ${files})
set_target_properties(pydicomifier_bruker PROPERTIES OUTPUT_NAME bruker)
if(APPLE)
    set_target_properties(pydicomifier_bruker PROPERTIES SUFFIX ".so")
endif()

target_link_libraries(
    pydicomifier_bruker ${Boost_LIBRARIES} libdicomifier ${JsonCpp_LIBRARIES}
    ${PYTHON_LIBRARIES})

install(
    TARGETS pydicomifier_bruker
    DESTINATION ${CMAKE_INSTALL_PREFIX}/${PYTHON_SITE_PACKAGES}/dicomifier
)
