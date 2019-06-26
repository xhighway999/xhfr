project(gui)
cmake_minimum_required(VERSION 2.6)

add_library(gui STATIC
    Dockspace.hpp
    Dockspace.cpp
    Widgets.hpp
    Widgets.cpp
    Window.hpp
    Window.cpp
    WindowManagerBase.hpp
    WindowManagerImpl.hpp
    WindowManagerImpl.cpp
)

target_link_libraries(gui imgui)
