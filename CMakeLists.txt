cmake_minimum_required(VERSION 3.10)
project(untitled)

set(CMAKE_CXX_STANDARD 11)

add_executable(untitled
    src/untitled.cc src/untitled.h
    src/camera.cc src/camera.h
    src/sphere.cc src/sphere.h
    src/transform.cc src/transform.h
    src/geometry.cc src/geometry.h
)
