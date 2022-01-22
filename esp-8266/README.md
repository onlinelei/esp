# esp-8266
esp-8266 工具集合

# 一、Quick Start

## 1.1 环境

- C++ 环境
- platformIo
- visual Studio Code 或者使用 Clion，可以根据个人爱好选择， Clion 效率更高点
- 一个可爱的开发板（esp8266）

## 1.2  


# 二、项目介绍
项目包含了各种基本操作的代码，分模块来开发。方便了调用，开发自己的功能时只用调用对应的模块工具类的方法

## 2.1 目录结构

``` shell
├── CMakeLists.txt  # CMake file 
├── LICENSE       
├── README.md
├── doc             # 使用到的文档
│   ├── 0a-esp8266ex_datasheet_cn.pdf
│   └── esp8266_source.md
├── platformio.ini  # Ploaformio 配置文件
├── src             # 代码
│   ├── demo  # 启动 demo
│   │   ├── printDemo.md
│   │   ├── webServerDemo.md
│   │   └── wifiDemo.md
│   ├── file                        # 文件操作工具类
│   │   ├── FileUtils.cpp
│   │   └── FileUtils.h
│   ├── led                         # led 工具类
│   ├── log                         # 日志相关工具类
│   │   ├── LogUtil.cpp
│   │   └── LogUtil.h
│   ├── main.cpp                    # 主函数
│   ├── net                         # 网络相关工具类
│   │   ├── HttpUtil.cpp
│   │   └── HttpUtil.h
│   ├── serial                      # 串口相关工具类
│   │   ├── SerialUtil.cpp
│   │   └── SerialUtil.h
│   ├── service                     # 服务相关工具类
│   │   ├── WebServer.cpp
│   │   └── WebServer.h
│   ├── time                        # 时间相关工具类
│   │   ├── NTPUtil.cpp
│   │   └── NTPUtil.h
│   └── wifi                        # wifi 相关工具类
│       ├── WifiUtil.cpp
│       └── WifiUtil.h
└── test                       # 测试包         
    ├── README
    └── test_demo.cpp
```

