find_package(Boost REQUIRED COMPONENTS python)
find_package(NIfTI REQUIRED)
find_package(PythonLibs 2.7 REQUIRED)

include_directories(
    ${CMAKE_SOURCE_DIR}/src/lib ${Boost_INCLUDE_DIRS} 
    ${NIfTI_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

file(GLOB files "*.cpp")
python_add_module(pydicomifier_nifti SHARED ${files})
set_target_properties(pydicomifier_nifti PROPERTIES OUTPUT_NAME nifti)
if(APPLE)
    set_target_properties(pydicomifier_nifti PROPERTIES SUFFIX ".so")
endif()

target_link_libraries(
    pydicomifier_nifti ${Boost_LIBRARIES} libdicomifier ${NIfTI_LIBRARIES} 
    ${PYTHON_LIBRARIES})

install(
    TARGETS pydicomifier_nifti
    DESTINATION ${CMAKE_INSTALL_PREFIX}/${PYTHON_SITE_PACKAGES}/dicomifier
)
