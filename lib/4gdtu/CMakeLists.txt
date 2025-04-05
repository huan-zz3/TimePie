cmake_minimum_required(VERSION 3.10)
project(4gdtu)
set(CMAKE_C++_STANDARD 11)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SOURCES)
add_library(4gdtu STATIC ${SOURCES})

target_link_libraries(4gdtu PUBLIC 
    macro
    serialib
    libtimer
)
target_include_directories(4gdtu PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)


