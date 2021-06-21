project(nanovg-nanort)
cmake_minimum_required(VERSION 2.6)


add_library(nanovg-nanort STATIC
nanovg-nanort/src/fontstash.h  
nanovg-nanort/src/nanovg.c  
nanovg-nanort/src/nanovg_rt.h 
nanovg-nanort/src/nanort.h
nanovg-nanort/src/nanovg.h
cmakescripts/nanort.cpp
)
target_link_libraries(nanovg-nanort PUBLIC stb)
#needed for emscripten
target_compile_options(nanovg-nanort PUBLIC -Wno-error=implicit-function-declaration)
target_include_directories(nanovg-nanort PUBLIC nanovg-nanort/src)
