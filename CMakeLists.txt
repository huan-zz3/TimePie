cmake_minimum_required(VERSION 3.10)
project(TimePie)

# 设置C++标准
set(CMAKE_CXX_STANDARD 14)

# 指定工具链文件
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/toolchain.cmake")

# 添加子目录
add_subdirectory(src)
add_subdirectory(lib)

#add_executable(TimePie
#        ${PROJECT_SOURCE_DIR}/src/main.cpp
#        ${PROJECT_SOURCE_DIR}/include/interface.h
#        ${PROJECT_SOURCE_DIR}/include/predefine.h
#        EPDriver
#)
