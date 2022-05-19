project(xhfr)

set (CMAKE_CXX_STANDARD 17)

add_subdirectory(gui)
add_subdirectory(fs)

if(${xhfr_audio})
    add_subdirectory(audio)
endif()


add_subdirectory(core)



add_library(xhfr STATIC
    xhfr.hpp
    xhfr.cpp)


target_link_libraries(xhfr PUBLIC imgui stb gui backend fs xhfr_core spdlog)

if(${xhfr_canvas})
    target_compile_definitions(xhfr PUBLIC XHFR_CANVAS)
endif()


target_include_directories(xhfr INTERFACE ../src)

target_include_directories(xhfr PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


