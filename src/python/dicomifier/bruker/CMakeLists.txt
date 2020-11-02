find_package(PythonInterp 3.5 REQUIRED)
find_package(pybind11 2.0 REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/src/lib ${PYTHON_INCLUDE_DIRS})

file(GLOB files "*.cpp")
add_definitions(-DBOOST_ALL_DYN_LINK)

pybind11_add_module(pydicomifier_bruker SHARED ${files})

set_target_properties(pydicomifier_bruker PROPERTIES OUTPUT_NAME bruker)
if(APPLE)
    set_target_properties(pydicomifier_bruker PROPERTIES SUFFIX ".so")
endif()

target_link_libraries(pydicomifier_bruker PUBLIC libdicomifier)

execute_process(
    COMMAND ${PYTHON_EXECUTABLE}
      -c "import os; \
        from distutils.sysconfig import *; \
        print(get_python_lib(True, prefix='').replace(os.path.sep, '/'))"
    OUTPUT_VARIABLE PYTHON_SITE_PACKAGES
    OUTPUT_STRIP_TRAILING_WHITESPACE)

install(
    TARGETS pydicomifier_bruker
    DESTINATION ${CMAKE_INSTALL_PREFIX}/${PYTHON_SITE_PACKAGES}/dicomifier
)
