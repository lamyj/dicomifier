find_package(PythonInterp REQUIRED)

execute_process(
    COMMAND ${PYTHON_EXECUTABLE}
      -c "import os; \
        from distutils.sysconfig import *; \
        print(get_python_lib(True, prefix='').replace(os.path.sep, '/'))"
    OUTPUT_VARIABLE PYTHON_SITE_PACKAGES
    OUTPUT_STRIP_TRAILING_WHITESPACE)
set(PYTHON_SITE_PACKAGES "${PYTHON_SITE_PACKAGES}" CACHE INTERNAL "Relative package path")

add_subdirectory(dicomifier)

install(
    DIRECTORY .
    DESTINATION ${CMAKE_INSTALL_PREFIX}/${PYTHON_SITE_PACKAGES}
    FILES_MATCHING PATTERN *.py
    # Avoid empty directory
    PATTERN "bruker" EXCLUDE
)

file(GLOB_RECURSE python_files "*.py")
add_custom_target(
    PythonFiles ${CMAKE_COMMAND} -E echo "Python files" SOURCES ${python_files})
