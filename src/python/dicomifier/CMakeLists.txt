find_package(Boost REQUIRED COMPONENTS python)
find_package(PythonLibs 2.7 REQUIRED)

add_subdirectory(bruker)
add_subdirectory(nifti)

include_directories(
    ${CMAKE_SOURCE_DIR}/src/lib ${Boost_INCLUDE_DIRS}
    ${PYTHON_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

file(GLOB files "*.cpp")
python_add_module(pydicomifier_dicomifier SHARED ${files})
set_target_properties(pydicomifier_dicomifier PROPERTIES OUTPUT_NAME _dicomifier)
if(APPLE)
    set_target_properties(pydicomifier_dicomifier PROPERTIES SUFFIX ".so")
endif()

target_link_libraries(
    pydicomifier_dicomifier ${Boost_LIBRARIES} libdicomifier ${PYTHON_LIBRARIES})

install(
    TARGETS pydicomifier_dicomifier
    DESTINATION ${CMAKE_INSTALL_PREFIX}/${PYTHON_SITE_PACKAGES}/dicomifier
)
