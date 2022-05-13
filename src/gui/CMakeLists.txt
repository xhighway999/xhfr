project(gui)
cmake_minimum_required(VERSION 3.14.5)

add_subdirectory(backends)
add_subdirectory(widgets)

if(${xhfr_FreeType})
    set(IMGUI_FREETYPE imgui_freetype.h imgui_freetype.cpp)
endif()


if(${xhfr_canvas})
     set(XHFR_CANVAS Canvas.hpp Canvas.cpp)
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
    FileDialog.hpp
    FileDialog.cpp
    WindowManagerBase.hpp
    WindowManagerImpl.hpp
    WindowManagerImpl.cpp
    Fonts.hpp
    Fonts.cpp
    DropEvent.hpp
    Styles.hpp
    Styles.cpp
    ${IMGUI_FREETYPE}
    ${XHFR_CANVAS}
)

if(${xhfr_FreeType})
    target_compile_definitions(gui PUBLIC XHFR_FREETYPE)
    target_link_libraries(gui freetype)
endif()

if(${xhfr_canvas})
    target_link_libraries(gui nanovg-nanort)
endif()


target_link_libraries(gui imgui fs stb backend widgets nfd)
