find_package(DCMTK REQUIRED)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
    
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)

add_definitions(-DHAVE_CONFIG_H)
ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

file(GLOB_RECURSE tests *.cpp)
foreach(test_file ${tests})
    get_filename_component(test ${test_file} NAME_WE)
    link_directories ( ${Boost_LIBRARY_DIRS} )
    add_executable(${test} ${test_file})
    target_link_libraries(${test} librouter ${Boost_LIBRARIES})
    add_test(NAME ${test} COMMAND ${test})
    #file(READ ${test_file} content)
    #string(REGEX MATCHALL "BOOST_AUTO_TEST_CASE\\([^)]+" fixtures ${content})
    #foreach(fixture ${fixtures})
    #    string(REGEX REPLACE "BOOST_AUTO_TEST_CASE\\(([^)]+)" "\\1" fixture ${fixture})
    #    # FIXME : 
    #    add_test("${test}_${fixture}" "${test}" "--run_test=${fixture}")
    #endforeach(fixture)
endforeach()
