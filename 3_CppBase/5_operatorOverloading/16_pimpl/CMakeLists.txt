cmake_minimum_required(VERSION 3.16)
project(LineLibDemo LANGUAGES CXX)

# C++标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 头文件搜索路径，让main.cc可以找到Line.h
include_directories(${CMAKE_SOURCE_DIR})

# --------------------------
# 1. 动态库 SHARED → libLine.so
# --------------------------
add_library(LineShared SHARED
        LineImpl.cpp
        Line.h
)
# 设置输出库文件名：libLine.so（去掉Shared后缀）
set_target_properties(LineShared PROPERTIES
        OUTPUT_NAME "Line"
)

# --------------------------
# 2. 静态库 STATIC → libLine.a
# --------------------------
add_library(LineStatic STATIC
        LineImpl.cpp
        Line.h
)
set_target_properties(LineStatic PROPERTIES
        OUTPUT_NAME "Line"
)

# --------------------------
# 3. 测试可执行程序（链接动态库版本）
# --------------------------
add_executable(test_dynamic test.cpp)
target_link_libraries(test_dynamic PRIVATE LineShared)

# 设置rpath：把库搜索路径打进可执行文件，运行时直接找到libLine.so，不用配置LD_LIBRARY_PATH
set_target_properties(test_dynamic PROPERTIES
        INSTALL_RPATH "$ORIGIN"
        BUILD_RPATH "$CMAKE_BINARY_DIR"
)

# --------------------------
# 4. 测试可执行程序（链接静态库版本）
# --------------------------
add_executable(test_static test.cpp)
target_link_libraries(test_static PRIVATE LineStatic)



## 创建构建目录
#mkdir build && cd build
#
## cmake生成构建脚本
#cmake ..
#
## 编译全部：静态库、动态库、两个测试程序
#make -j4