cmake_minimum_required(VERSION 3.10)

project(serialib)

set(CMAKE_C++_STANDARD 11)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# 指定所有源文件
set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/serialib.cpp

)

# 生成静态库
add_library(serialib STATIC ${SOURCES})
# add_library(serialib SHARED ${SOURCES})

# target_compile_definitions(serialib PRIVATE USE_LGPIO_LIB)
# target_include_directories(EPDriver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../lg)
target_link_libraries(${PROJECT_NAME} PRIVATE 
    
)
target_include_directories(serialib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# 如果需要共享库，可以使用以下命令代替：
# add_library(serialib SHARED ${SOURCES})


