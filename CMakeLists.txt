cmake_minimum_required(VERSION 3.28)
project(RayEngine)

set(CMAKE_CXX_STANDARD 17)

add_executable(RayEngine main.cpp
        cpu_renderer.cpp
        cpu_renderer.h
        vec3.h)
