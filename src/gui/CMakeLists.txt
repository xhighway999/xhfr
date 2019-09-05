project(gui)
cmake_minimum_required(VERSION 3.14.5)

add_subdirectory(backends)

add_library(gui STATIC
    Dockspace.hpp
    Dockspace.cpp
    Image.hpp
    Image.cpp
    Widgets.hpp
    Widgets.cpp
    Window.hpp
    Window.cpp
    WindowManagerBase.hpp
    WindowManagerImpl.hpp
    WindowManagerImpl.cpp
)

if(${xhfr_FreeType})
target_link_libraries(gui imgui fs stb backend)
