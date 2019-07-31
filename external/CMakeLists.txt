

include(cmakescripts/imgui.cmake)
include(cmakescripts/luajit.cmake)
include(cmakescripts/glfw.cmake)

add_subdirectory(stb)
add_subdirectory(sol2)

if(${xhfr_Backend} STREQUAL "sdl")
add_subdirectory(glad)
add_subdirectory(sdl)
else()
add_subdirectory(glad)
add_subdirectory(glfw)
endif()
