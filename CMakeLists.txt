cmake_minimum_required(VERSION 3.10)
project(untitled)

set(CMAKE_CXX_STANDARD 11)

set(core_source
    src/camera.cc
    src/geometry.cc
    src/transform.cc
#    src/shape.cc
    src/sphere.cc
)

set(core_headers
    src/camera.h
    src/geometry.h
    src/transform.h
#    src/shape.h
    src/sphere.h
    src/untitled.h
)

add_library(lib
    ${core_source}
    ${core_headers}
)

add_executable(untitled src/untitled.cc)

target_link_libraries(untitled ${lib})
