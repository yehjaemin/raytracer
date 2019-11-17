cmake_minimum_required(VERSION 3.10)
project(untitled)

set(CMAKE_CXX_STANDARD 11)

set(core_source
    src/geometry.cc
    src/shape.cc
)

set(core_headers
    src/geometry.h
    src/shape.h
)

add_library(lib
    ${core_source}
    ${core_headers}
)

add_executable(untitled src/untitled.cc)

target_link_libraries(untitled ${lib})
