cmake_minimum_required(VERSION 3.10)
project(epdcpp)
set(CMAKE_C++_STANDARD 11)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SOURCES)
add_library(epdcpp STATIC ${SOURCES})

target_link_libraries(epdcpp PUBLIC 
    macro
    EPDriver
)
target_include_directories(epdcpp PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)


