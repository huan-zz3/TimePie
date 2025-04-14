# 项目目录结构

```bash
huanzze@babyhuanzze:~/dev/TimePie$ tree -Ld 3
.
├── catch-test                 # 使用catch2作为测试框架编写的部分测试
│   ├── CMakeLists.txt
│   ├── <.......-tests(s)>
├── example                    # 项目内各功能的使用示例（有可能未更新api）
│   ├── CMakeLists.txt
│   ├── <......._example(s)>
├── lib                        # 项目内使用的外部库（thirdparty）和自编写封装库
│   ├── CMakeLists.txt
│   ├── 4gdtu                     # 对“中移ML307R 4G Cat1 DTU版本”通信模块功能做的封装
│   ├── epdcpp                    # 对微雪触摸墨水屏官方库做的C++11封装
│   ├── libtimer                  # 多线程定时触发器（类似于QtQTimer类）
│   ├── macro                     # 项目范围内通用的头文件定义
│   ├── sqlite3cpp                # 对sqlite3做的C++11封装
│   └── thirdparty                # 项目使用的外部库（源码+静态库链接/动态库链接）
│       ├── EPDriver              # 微雪官方触摸墨水屏的C代码（经过整理改bug）
│       ├── eventpp               # 事件驱动库
│       ├── glog                  # 日志库
│       ├── lg                    # GPIO/I2C/SPI控制库
│       ├── libsigc++-2.0         # 信号库（类似于Qt信号与槽系统）
│       ├── serialib              # 串口库
│       └── sqlite                # sqlite本地数据库
├── src
│   ├── CMakeLists.txt
│   ├── bgservice                # 后台服务代码
│   ├── eventbus                 # 事件种类定义、C++11封装、全局唯一实例
│   │   ├── categories
│   ├── gui                      # 组件与页面实现代码
│   │   ├── components
│   │   └── pages
│   ├── interaction              # 人机交互
│   │   ├── loglight             # LED提示灯
│   │   ├── physicalkey          # 物理按键
│   │   └── screentouch          # 触屏
│   ├── timebook                 # 与“TimeBook时间书”服务后端的对接实现
│   ├── main.cpp                 # 程序入口代码
│   └── systeminitializer.hpp    # 系统初始化独立文件定义
├── toolchain.cmake              # 交叉编译配置文件
├── README.md
├── changelog
└── CMakeLists.txt
```