# CMake最低版本要求
cmake_minimum_required(VERSION 3.15.0)
# 项目信息
project(ChatServer)
# 指定生成目标
add_executable(ChatServer server.cpp)