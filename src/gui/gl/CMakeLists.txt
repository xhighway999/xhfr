project(gl)
cmake_minimum_required(VERSION 2.6)


add_library(glbackend STATIC
    Backend.hpp
    )
target_compile_definitions(glbackend PRIVATE XHFR_GL_BACKEND=${BACKEND})

if("${xhfr_Backend}" STREQUAL "sdl")
  add_subdirectory(sdl_opengl3)
  target_link_libraries(glbackend SDL2-static imgui_impl_sdl2)
  set(BACKEND 2)
elseif("${xhfr_Backend}" STREQUAL "sdl-ems")
    add_subdirectory(sdl_ems)
    target_link_libraries(glbackend imgui_impl_sdl2_ems)
    set(BACKEND 3)
else()
  add_subdirectory(glfw_opengl3)
  target_link_libraries(glbackend glfw glad imgui_impl_glfw)
  set(BACKEND 1)
endif()
