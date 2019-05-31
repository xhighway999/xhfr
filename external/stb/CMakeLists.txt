project(stb)
cmake_minimum_required(VERSION 2.6)



add_library(stb STATIC
    stb.cpp
    stb/stb_vorbis.c
)
target_include_directories(stb PUBLIC stb)
