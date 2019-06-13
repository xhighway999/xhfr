project(devtools)
cmake_minimum_required(VERSION 2.6)



add_library(devtools STATIC
    AbstractTool.h
    AbstractTool.cpp
)
target_include_directories(devtools PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )

target_link_libraries(devtools imgui)
