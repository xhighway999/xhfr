cmake_minimum_required(VERSION 3.14.5)



include(cmakescripts/imgui.cmake)
include(cmakescripts/glfw.cmake)
include(cmakescripts/nanovg-nanort.cmake)

if(NOT ${xhfr_spdlog_external})
    add_subdirectory(spdlog)
endif()

if(NOT ${xhfr_stb_external})
  add_subdirectory(stb)
endif()

if(NOT ${xhfr_json_external})

    set(JSON_BuildTests OFF CACHE INTERNAL "")
  add_subdirectory(json)
endif()

if(NOT ${xhfr_PhysFs_external})
    #stop physfs conflicting with glfw
    set(PHYSFS_TARGETNAME_DOCS "physfs_docs" CACHE STRING "physfs_docs" )
    add_subdirectory(physfs)
endif()
if(${xhfr_FreeType})
    include(cmakescripts/freetype.cmake)
endif()


#dependencies required for xhfr audio

if(${xhfr_audio})
SET(wave_enable_tests OFF CACHE BOOL "" FORCE)
    add_subdirectory(wave)
endif()



if(${xhfr_Backend} STREQUAL "sdl")
    add_subdirectory(glad)
    add_subdirectory(sdl)
elseif(${xhfr_Backend} STREQUAL "sdl-ems")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s ERROR_ON_UNDEFINED_SYMBOLS=0 -s USE_SDL=2 -s USE_WEBGL2=1 -s WASM=1 -s FULL_ES3=1 -s ALLOW_MEMORY_GROWTH=1")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s ERROR_ON_UNDEFINED_SYMBOLS=0 -s USE_SDL=2 -s USE_WEBGL2=1 -s WASM=1 -s FULL_ES3=1 -s ALLOW_MEMORY_GROWTH=1")
else()
    add_subdirectory(glad)
    add_subdirectory(glfw)
endif()

add_subdirectory(nativefiledialog-extended)
