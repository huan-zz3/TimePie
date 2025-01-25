# 设置交叉编译系统
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)  # 这里假设你的目标处理器是 ARM 架构

# 设置交叉编译器路径
set(CMAKE_C_COMPILER /home/huanzze/dev/luckfox-pico/tools/linux/toolchain/arm-rockchip830-linux-uclibcgnueabihf/bin/arm-rockchip830-linux-uclibcgnueabihf-gcc)
set(CMAKE_CXX_COMPILER /home/huanzze/dev/luckfox-pico/tools/linux/toolchain/arm-rockchip830-linux-uclibcgnueabihf/bin/arm-rockchip830-linux-uclibcgnueabihf-g++)

# 设置交叉编译器的库和头文件路径
set(CMAKE_FIND_ROOT_PATH /home/huanzze/dev/luckfox-pico/tools/linux/toolchain/arm-rockchip830-linux-uclibcgnueabihf)

# 还需要指定库的搜索路径
set(CMAKE_LIBRARY_PATH ${CMAKE_FIND_ROOT_PATH}/lib ${CMAKE_FIND_ROOT_PATH}/lib64)

# 指定交叉编译的头文件路径（如果有）
set(CMAKE_INCLUDE_PATH ${CMAKE_FIND_ROOT_PATH}/include)

# 如果需要将交叉编译器的动态库路径添加到 CMake 中进行查找
set(CMAKE_FIND_LIBRARY_PREFIXES "")

# 在查找时，忽略主机系统的路径，避免查找本机的库
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
