project(imgui)
cmake_minimum_required(VERSION 2.6)


add_library(imgui STATIC
    imgui/imconfig.h
    imgui/imgui.h
    imgui/imgui_internal.h
    imgui/imstb_rectpack.h
    imgui/imstb_textedit.h
    imgui/imgui_tables.cpp
    imgui/imstb_truetype.h
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
)

target_include_directories(imgui PUBLIC imgui)
