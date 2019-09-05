project(imgui_impl_sdl2)
cmake_minimum_required(VERSION 2.6)





add_library(imgui_impl_sdl2 STATIC
    imgui_impl_sdl.cpp
    imgui_impl_opengl3.cpp
    sdl2_backend.cpp
)
target_compile_definitions(imgui_impl_sdl2 PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)
target_include_directories(imgui_impl_sdl2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(imgui_impl_sdl2 glad imgui SDL2-static)
