

include(cmakescripts/imgui.cmake)
include(cmakescripts/glfw.cmake)

if(${xhfr_LuaJit})
    include(cmakescripts/luajit.cmake)
else()
    add_subdirectory(lua)
    ##neded for emscripten
    include_directories(SYSTEM lua/src)
endif()

add_subdirectory(stb)
add_subdirectory(sol2)

if(${xhfr_Backend} STREQUAL "sdl")
add_subdirectory(glad)
add_subdirectory(sdl)
else()
add_subdirectory(glad)
add_subdirectory(glfw)
endif()
