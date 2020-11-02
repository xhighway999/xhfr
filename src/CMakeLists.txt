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
if(${xhfr_LuaJit})
    target_link_libraries(xhfr PUBLIC luajit)
    target_include_directories(xhfr PUBLIC ../external/luajit/src/)
else()
    target_link_libraries(xhfr PUBLIC liblua)
endif()

target_link_libraries(xhfr PUBLIC sol2 imgui stb gui backend fs xhfr_core spdlog)
target_include_directories(xhfr INTERFACE ../src)

target_include_directories(xhfr PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

