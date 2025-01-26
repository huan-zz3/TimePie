# 设置 CMake 的最低版本要求
cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(EPDriver)

# 设置 C 标准
set(CMAKE_C_STANDARD 99)

# 包含头文件目录（你可以将所有头文件路径传给 target_include_directories）
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/Config
        ${CMAKE_CURRENT_SOURCE_DIR}/Driver
        ${CMAKE_CURRENT_SOURCE_DIR}/EPD
        ${CMAKE_CURRENT_SOURCE_DIR}/Fonts
        ${CMAKE_CURRENT_SOURCE_DIR}/GUI
)

# 指定所有源文件
set(SOURCES
        # Config 文件
        ${CMAKE_CURRENT_SOURCE_DIR}/Config/DEV_Config.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/Config/dev_hardware_i2c.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/Config/dev_hardware_SPI.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/Config/RPI_gpiod.c

        # Driver 文件
        ${CMAKE_CURRENT_SOURCE_DIR}/Driver/GT1151.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/Driver/ICNT86X.c

        # EPD 文件
#        ${CMAKE_CURRENT_SOURCE_DIR}/EPD/EPD_2in13_V2.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/EPD/EPD_2in13_V3.c
        ${CMAKE_CURRENT_SOURCE_DIR}/EPD/EPD_2in13_V4.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/EPD/EPD_2in9_V2.c

        # Fonts 文件
        ${CMAKE_CURRENT_SOURCE_DIR}/Fonts/font12.c
        ${CMAKE_CURRENT_SOURCE_DIR}/Fonts/font12CN.c
        ${CMAKE_CURRENT_SOURCE_DIR}/Fonts/font16.c
        ${CMAKE_CURRENT_SOURCE_DIR}/Fonts/font20.c
        ${CMAKE_CURRENT_SOURCE_DIR}/Fonts/font24.c
        ${CMAKE_CURRENT_SOURCE_DIR}/Fonts/font24CN.c
        ${CMAKE_CURRENT_SOURCE_DIR}/Fonts/font8.c

        # GUI 文件
        ${CMAKE_CURRENT_SOURCE_DIR}/GUI/GUI_BMPfile.c
        ${CMAKE_CURRENT_SOURCE_DIR}/GUI/GUI_Paint.c
)

# 生成静态库
add_library(EPDriver STATIC ${SOURCES})

# 如果需要共享库，可以使用以下命令代替：
# add_library(EPDriver SHARED ${SOURCES})

# 你可以选择将库链接到目标，假设目标是主项目中的可执行文件
# target_link_libraries(your_target EPDriver)

