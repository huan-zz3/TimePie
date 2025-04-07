cmake_minimum_required(VERSION 3.10)
project(TimePie)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/toolchain.cmake")

# include_directories(${PROJECT_SOURCE_DIR}/macro)

add_subdirectory(src)
add_subdirectory(lib)
add_subdirectory(example)
# add_subdirectory(catch-test)