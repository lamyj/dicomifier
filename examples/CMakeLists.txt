find_package(Odil REQUIRED)
find_package(V8 REQUIRED)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/lib
    ${Odil_INCLUDE_DIRS} ${V8_INCLUDE_DIRS})

add_executable(javascriptvm javascriptvm.cpp)
target_link_libraries(javascriptvm libdicomifier ${V8_LIBRARIES})
