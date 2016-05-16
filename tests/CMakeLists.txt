find_package(Boost COMPONENTS filesystem system unit_test_framework REQUIRED)
find_package(DCMTK REQUIRED)
find_package(JsonCpp REQUIRED)
find_package(Odil REQUIRED)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/lib
    ${Boost_INCLUDE_DIRS} ${DCMTK_INCLUDE_DIRS} ${JsonCpp_INCLUDE_DIRS} 
    ${Odil_INCLUDE_DIRS})
add_definitions(
    ${DCMTK_DEFINITIONS} -DBOOST_FILESYSTEM_VERSION=3 -DBOOST_TEST_DYN_LINK)
link_directories(
    ${Boost_LIBRARY_DIRS})

add_custom_target(
    Runner ${CMAKE_COMMAND} -E echo "Test runner" SOURCES run_tests.sh)

file(GLOB_RECURSE tests *.cpp)
foreach(test_file ${tests})
    get_filename_component(test ${test_file} NAME_WE)
    add_executable(${test} ${test_file})
    target_link_libraries(
        ${test}
        libdicomifier
        ${Boost_LIBRARIES} ${JsonCpp_LIBRARIES} ${Odil_LIBRARIES})

    file(READ ${test_file} content)    

    set(pattern "BOOST_(AUTO|FIXTURE)_TEST_CASE\\(([^),]+)")
    
    string(REGEX MATCHALL ${pattern} cases ${content})
    
    foreach(case ${cases})
        string(REGEX REPLACE ${pattern} "\\2" case ${case})
        add_test("${test}_${case}" "${test}" "--run_test=${case}")
    endforeach()
endforeach()
