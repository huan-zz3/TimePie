cmake_minimum_required(VERSION 3.10)
project(libtimer)
set(CMAKE_C++_STANDARD 11)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/timer.cpp

)
add_library(libtimer STATIC ${SOURCES})
# add_library(libtimer SHARED ${SOURCES})

target_include_directories(libtimer PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)


