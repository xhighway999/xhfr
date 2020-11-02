project(gui)
cmake_minimum_required(VERSION 3.14.5)

add_library(widgets STATIC
    Bezier.hpp
    Bezier.cpp
)

target_link_libraries(widgets gui)



