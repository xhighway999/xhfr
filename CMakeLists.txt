cmake_minimum_required(VERSION 3.14.5)

option(xhfr_TinyMode "Tiny Mode" OFF)
option(xhfr_DevMode "Developer Mode" OFF)
option(xhfr_LuaJit "Use Luajit" OFF)
set(xhfr_Backend "glfw" CACHE STRING "What backend to use. Valid options: glfw, sdl, sdl-ems")


set (CMAKE_CXX_STANDARD 17)

if(${xhfr_TinyMode})
    set(SIZE_FLAGS "-ffunction-sections -fdata-sections")
    message("Using Tiny Mode")
    add_compile_options(-Os -s -fdata-sections -ffast-math -ffunction-sections -fno-stack-protector -fno-unwind-tables -fno-asynchronous-unwind-tables)
endif()

include_directories(PUBLIC external)
add_subdirectory(external)
add_subdirectory(src)

# strip -s -R .comment -R .gnu.version --strip-unneeded
# strip -S --strip-unneeded --remove-section=.note.gnu.gold-version --remove-section=.comment --remove-section=.note --remove-section=.note.gnu.build-id --remove-section=.note.ABI-tag
#upx -9 --lzma roboeye
