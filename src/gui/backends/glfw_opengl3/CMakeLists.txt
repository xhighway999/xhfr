project(imgui_impl_glfw)
cmake_minimum_required(VERSION 2.6)





add_library(imgui_impl_glfw STATIC
    imgui_impl_glfw.h
    imgui_impl_glfw.cpp
    imgui_impl_opengl3.cpp
    imgui_impl_opengl3.h
    glfw_backend.cpp
)
target_compile_definitions(imgui_impl_glfw PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)
target_include_directories(imgui_impl_glfw PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(imgui_impl_glfw glad glfw imgui xhfr_core)
