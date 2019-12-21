cmake_minimum_required(VERSION 3.10)
project(untitled)

set(CMAKE_CXX_STANDARD 11)

add_executable(untitled
    src/untitled.cc src/untitled.h
    src/camera.cc src/camera.h
    src/sphere.cc src/sphere.h
    src/geometry.cc src/geometry.h
)

#set(core_source
#    src/camera.cc
#    src/geometry.cc
##    src/transform.cc
##    src/shape.cc
#    src/sphere.cc
#)
#
#set(core_headers
#    src/camera.h
#    src/geometry.h
##    src/transform.h
##    src/shape.h
#    src/sphere.h
##    src/untitled.h
#)
#
#add_library(lib
#    ${core_headers}
#    ${core_source}
#)
#
#add_executable(untitled src/untitled.cc)
#
#target_link_libraries(untitled ${lib})
