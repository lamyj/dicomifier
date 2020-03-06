find_package(Boost COMPONENTS filesystem system unit_test_framework REQUIRED)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/lib ${Boost_INCLUDE_DIRS})
add_definitions(-DBOOST_FILESYSTEM_VERSION=3 -DBOOST_TEST_DYN_LINK)
link_directories(${Boost_LIBRARY_DIRS})

file(GLOB_RECURSE tests *.cpp)
foreach(test_file ${tests})
    get_filename_component(test ${test_file} NAME_WE)
    add_executable(${test} ${test_file})
    target_link_libraries(
        ${test}
        libdicomifier
        ${Boost_LIBRARIES} ${JsonCpp_LIBRARIES})

    file(READ ${test_file} content)    

    set(pattern "BOOST_(AUTO|FIXTURE)_TEST_CASE\\(([^),]+)")
    
    string(REGEX MATCHALL ${pattern} cases ${content})
    
    foreach(case ${cases})
        string(REGEX REPLACE ${pattern} "\\2" case ${case})
        add_test("${test}_${case}" "${test}" "--run_test=${case}")
    endforeach()
endforeach()

file(GLOB_RECURSE python_tests "*.py")
add_custom_target(
    PythonTests ${CMAKE_COMMAND} -E echo "Python tests" SOURCES ${python_tests})
