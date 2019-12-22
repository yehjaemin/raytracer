cmake_minimum_required(VERSION 3.10)
project(untitled)

set(CMAKE_CXX_STANDARD 11)

include_directories(src)
include_directories(src/core)
include_directories(src/shapes)

add_executable(untitled
    src/main/untitled.cc    src/core/untitled.h
    src/core/integrator.cc  src/core/integrator.h
    src/core/camera.cc      src/core/camera.h
    src/shapes/sphere.cc    src/shapes/sphere.h
    src/core/shape.cc       src/core/shape.h
    src/core/film.cc        src/core/film.h
    src/core/transform.cc   src/core/transform.h
    src/core/geometry.cc    src/core/geometry.h
)
