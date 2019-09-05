project(gui)
cmake_minimum_required(VERSION 3.14.5)

add_subdirectory(backends)

if(${xhfr_FreeType})
    set(IMGUI_FREETYPE imgui_freetype.h imgui_freetype.cpp)
endif()

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
    Fonts.hpp
    Fonts.cpp
    ${IMGUI_FREETYPE}
)

if(${xhfr_FreeType})
    target_compile_definitions(gui PUBLIC XHFR_FREETYPE)
    target_link_libraries(gui freetype)
endif()


target_link_libraries(gui imgui fs stb backend)
