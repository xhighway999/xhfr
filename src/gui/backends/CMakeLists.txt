project(gl)
cmake_minimum_required(VERSION 2.6)


add_library(backend STATIC
    Backend.hpp
    Backend.cpp
    )
target_compile_definitions(backend PRIVATE XHFR_GL_BACKEND=${BACKEND})

if("${xhfr_Backend}" STREQUAL "sdl")
  add_subdirectory(sdl_opengl3)
  target_include_directories(backend PRIVATE sdl_opengl3)
  target_link_libraries(backend SDL2-static imgui_impl_sdl2)
  set(BACKEND 2)
elseif("${xhfr_Backend}" STREQUAL "sdl-ems")
    add_subdirectory(sdl_ems)
    target_include_directories(backend PRIVATE sdl_ems)
    target_link_libraries(backend imgui_impl_sdl2_ems)
    set(BACKEND 3)
elseif("${xhfr_Backend}" STREQUAL "glfw")
  add_subdirectory(glfw_opengl3)
  target_include_directories(backend PRIVATE glfw_opengl3)
  target_link_libraries(backend glfw glad imgui_impl_glfw xhfr_core)
  set(BACKEND 1)
else()
    message(FATAL_ERROR "No valid backend")
endif()
