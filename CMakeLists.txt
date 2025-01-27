cmake_minimum_required(VERSION 3.10)
project(TimePie)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/toolchain.cmake")

add_subdirectory(src)
add_subdirectory(lib)

