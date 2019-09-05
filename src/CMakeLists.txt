project(xhfr)

add_subdirectory(gui)
add_subdirectory(fs)
add_library(xhfr STATIC
    xhfr.hpp
    xhfr.cpp)
if(${xhfr_LuaJit})
    target_link_libraries(xhfr luajit)
    target_include_directories(xhfr PUBLIC ../external/luajit/src/)
else()
    target_link_libraries(xhfr liblua)
endif()

target_link_libraries(xhfr sol2 imgui stb gui backend fs)
target_include_directories(xhfr INTERFACE ../src)

target_include_directories(xhfr PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

