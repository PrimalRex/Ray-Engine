cmake_minimum_required(VERSION 3.28)
project(RayEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")
add_executable(RayEngine main.cpp
        cpu_renderer.cpp
        cpu_renderer.h
        vec3.h
        world_object.cpp
        world_object.h
        scene.h)
