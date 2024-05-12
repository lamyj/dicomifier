file(GLOB_RECURSE python_tests "*.py")
add_custom_target(
    PythonTests ${CMAKE_COMMAND} -E echo "Python tests" SOURCES ${python_tests})
