project(imgui_impl_sdl2_ems )
cmake_minimum_required(VERSION 2.6)





add_library(imgui_impl_sdl2_ems STATIC
    imgui_impl_sdl.cpp
    imgui_impl_opengl3.cpp
    sdl2_backend.cpp
)

target_compile_definitions(imgui_impl_sdl2_ems PUBLIC IMGUI_IMPL_OPENGL_LOADER_SDL_GL2)
target_include_directories(imgui_impl_sdl2_ems PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(imgui_impl_sdl2_ems imgui)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -s USE_SDL=2 -s USE_WEBGL2=1 -s FULL_ES3=1")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -s USE_SDL=2 -s USE_WEBGL2=1 -s FULL_ES3=1")
