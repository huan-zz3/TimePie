cmake_minimum_required(VERSION 3.10)

project(EPDriver)

set(CMAKE_C_STANDARD 99)

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
target_compile_definitions(EPDriver PRIVATE USE_LGPIO_LIB)

# 如果需要共享库，可以使用以下命令代替：
# add_library(EPDriver SHARED ${SOURCES})


