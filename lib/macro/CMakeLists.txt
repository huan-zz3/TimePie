cmake_minimum_required(VERSION 3.10)
project(macro)
set(CMAKE_C++_STANDARD 11)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SOURCES)
add_library(macro STATIC ${SOURCES})

target_link_libraries(macro PUBLIC sigc++ glog)
target_include_directories(macro PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)


