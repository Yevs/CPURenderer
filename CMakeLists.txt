cmake_minimum_required(VERSION 3.2)
project(CPURenderer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
configure_file(obj/african_head.obj obj/african_head.obj COPYONLY)
add_executable(CPURenderer ${SOURCE_FILES} tgaimage.cpp tgaimage.h geometry.h Model.cpp Model.h)