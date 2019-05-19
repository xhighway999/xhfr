project(imgui_impl)
cmake_minimum_required(VERSION 2.6)

include_directories(PUBLIC imgui_impl)



add_library(imgui_impl STATIC
    imgui_impl_glfw.h
    imgui_impl_glfw.cpp
    imgui_impl_opengl3.cpp
    imgui_impl_opengl3.h
)
target_compile_definitions(imgui_impl PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)
target_include_directories(imgui_impl PUBLIC imgui_impl)
target_link_libraries(imgui_impl glad)
