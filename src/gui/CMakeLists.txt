project(gui)
cmake_minimum_required(VERSION 2.6)

add_subdirectory(gl)

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

target_link_libraries(gui imgui glbackend)
