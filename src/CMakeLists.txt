project(xhfr)

add_subdirectory(gui)

add_library(xhfr STATIC
    xhfr.hpp
    xhfr.cpp)
target_link_libraries(xhfr dl sol2 imgui imgui_impl glfw glad stb gui ${CMAKE_CURRENT_SOURCE_DIR}/../external/luajit/src/libluajit.a)
target_include_directories(xhfr PUBLIC ../external/luajit/src/)
target_include_directories(xhfr INTERFACE ../src)

target_include_directories(xhfr PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

