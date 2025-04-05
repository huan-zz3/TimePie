cmake_minimum_required(VERSION 3.10)
project(sqlite3cpp)
set(CMAKE_C++_STANDARD 11)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SOURCES)
add_library(sqlite3cpp STATIC ${SOURCES})

target_link_libraries(sqlite3cpp PUBLIC 
    sqlite
    macro
)
target_include_directories(sqlite3cpp PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)