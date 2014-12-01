cmake_minimum_required(VERSION 2.8)

add_definitions(-DHAVE_CONFIG_H)

macro(swig_python_module name)
    # Build a SWIG Python module. This macro is a wrapper around swig_add_module.
    find_package(SWIG REQUIRED)
    include(${SWIG_USE_FILE})

    set(cplusplus "OFF")

    foreach(it ${ARGN})
        if(${it} MATCHES ".*\\.i$")
            set(swig_dot_i_sources ${swig_dot_i_sources} "${it}")
        elseif(${it} MATCHES ".*\\.cpp$")
            set(cplusplus "ON")
        elseif(${it} MATCHES ".*\\.cxx$")
            set(cplusplus "ON")
        endif()
    endforeach()
    
    foreach(it ${swig_dot_i_sources})
        get_source_file_property(value ${it} CPLUSPLUS)
        if(${value} STREQUAL "NOTFOUND")
            set_source_files_properties(${it} PROPERTIES CPLUSPLUS ${cplusplus})
        endif()
    endforeach()
    
    find_package(PythonLibs)
    include_directories(${PYTHON_INCLUDE_PATH})
    
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                        ${CMAKE_CURRENT_SOURCE_DIR}/../lib)
    
    swig_add_module(${name} python ${ARGN})
    
    swig_link_libraries(${name} ${PYTHON_LIBRARIES})
endmacro(swig_python_module name)

find_package(PythonLibs)

set_source_files_properties(dicomifier.i PROPERTIES CPLUSPLUS ON)
include_directories(${PYTHON_INCLUDE_PATH})
include_directories(BEFORE "${CMAKE_CURRENT_SOURCE_DIR}/..")
swig_python_module(dicomifier dicomifier.i wrapper.cpp)
swig_link_libraries(dicomifier libdicomifier)

# copy all header files to the include directory
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        FILE_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
        DIRECTORY_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
        DESTINATION /usr/include/dicomifier/
        FILES_MATCHING PATTERN "*.h")
