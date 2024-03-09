find_package(Odil)
if(NOT "${Odil_FOUND}")
    find_file(Odil_INCLUDE odil/odil.h REQUIRED)
    # Get grand-parent of include file
    get_filename_component(Odil_INCLUDE_DIRS "${Odil_INCLUDE}" DIRECTORY)
    get_filename_component(Odil_INCLUDE_DIRS "${Odil_INCLUDE_DIRS}" DIRECTORY)
    find_library(Odil_LIBRARIES odil REQUIRED)
endif()
find_package(PythonInterp 3.5 REQUIRED)
find_package(pybind11 2.0 REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/src/lib ${PYTHON_INCLUDE_DIRS})

file(GLOB_RECURSE header_files "*.h")
file(GLOB_RECURSE template_files "*.txx")
file(GLOB_RECURSE source_files "*.cpp")
list(SORT header_files)
list(SORT source_files)
list(SORT template_files)

add_definitions(-DBOOST_ALL_DYN_LINK)

pybind11_add_module(
    pydicomifier_dicomifier SHARED
    ${header_files} ${source_files} ${template_files})

set_target_properties(pydicomifier_dicomifier PROPERTIES OUTPUT_NAME _dicomifier)
if(APPLE)
    set_target_properties(pydicomifier_dicomifier PROPERTIES SUFFIX ".so")
endif()

if("${Odil_FOUND}")
    target_link_libraries(
        pydicomifier_dicomifier PUBLIC libdicomifier Odil::libodil)
else()
    target_include_directories(
        pydicomifier_dicomifier PUBLIC ${Odil_INCLUDE_DIRS}) 
    target_link_libraries(
        pydicomifier_dicomifier PUBLIC libdicomifier ${Odil_LIBRARIES})
endif()

execute_process(
    COMMAND ${PYTHON_EXECUTABLE}
        -c "import os; import sysconfig; \
        print(\ 
            sysconfig.get_path('platlib', os.name+'_user', {'userbase': '.'})\
            .replace('\\\\', '/'))"
    OUTPUT_VARIABLE PYTHON_SITE_PACKAGES
    OUTPUT_STRIP_TRAILING_WHITESPACE)

install(
    TARGETS pydicomifier_dicomifier
    DESTINATION ${CMAKE_INSTALL_PREFIX}/${PYTHON_SITE_PACKAGES}/dicomifier
)
