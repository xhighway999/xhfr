cmake_minimum_required(VERSION 3.14.5)

option(xhfr_TinyMode "Tiny Mode" OFF)
option(xhfr_DevMode "Developer Mode" OFF)
option(xhfr_LuaJit "Use Luajit" OFF)
option(xhfr_FreeType "Use FreeType" ON)
option(xhfr_PhysFs_external "Use System/Parent PhysFS library" OFF)
option(xhfr_stb_external "Use System/Parent stb library" OFF)
option(xhfr_spdlog_external "Use System/Parent spdlog library" OFF)
option(xhfr_json_external "Use System/Parent json library" ON)
option(xhfr_audio "Build xhfr audio module" ON)

set(xhfr_trs_search_path "${CMAKE_CURRENT_SOURCE_DIR}/../" CACHE STRING "trs search path")
set(xhfr_trs_output_path "${CMAKE_CURRENT_SOURCE_DIR}/../data.c" CACHE STRING "trs output path")

set(xhfr_Backend "sdl" CACHE STRING "What backend to use. Valid options: glfw, sdl, sdl-ems")


set (CMAKE_CXX_STANDARD 17)

if(${xhfr_TinyMode})
    set(SIZE_FLAGS "-ffunction-sections -fdata-sections")
    message("Using Tiny Mode")
    add_compile_options(-Os -s -fdata-sections -ffast-math -ffunction-sections -fno-stack-protector -fno-unwind-tables -fno-asynchronous-unwind-tables)
endif()

include_directories(PUBLIC external)
add_subdirectory(external)
add_subdirectory(src)


macro(trs_add input output type)
    IF(CMAKE_CROSSCOMPILING)
      SET(trs "IMPORTFILE-NOTFOUND" CACHE FILEPATH "Point it to the export file from a native build")

      add_custom_target(
          UPDATE_RESOURCES
          COMMAND ${trs} -i ${input} -o ${output} -t ${type}
          #COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/mk_config_h.py ${CMAKE_CURRENT_BINARY_DIR}/config.h
      )

    else(CMAKE_CROSSCOMPILING)
    add_subdirectory(external/trs)
    add_custom_target(
        UPDATE_RESOURCES
        COMMAND trs -i ${input} -o ${output} -t ${type}
        #COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/mk_config_h.py ${CMAKE_CURRENT_BINARY_DIR}/config.h
    )
    endif(CMAKE_CROSSCOMPILING)
    add_dependencies(xhfr UPDATE_RESOURCES)
endmacro()

if(WIN32)
    #force msvc to use char, like every *sane* compiler
    target_compile_options(xhfr PUBLIC /utf-8)
    #force sdl to not fuck up the main function
    target_compile_definitions(xhfr PUBLIC SDL_MAIN_HANDLED)
endif(WIN32)
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

#trs_add(${CMAKE_CURRENT_SOURCE_DIR}/../ ${CMAKE_CURRENT_SOURCE_DIR}/../data.c c)
trs_add(${xhfr_trs_search_path} ${xhfr_trs_output_path} c)


# strip -s -R .comment -R .gnu.version --strip-unneeded
# strip -S --strip-unneeded --remove-section=.note.gnu.gold-version --remove-section=.comment --remove-section=.note --remove-section=.note.gnu.build-id --remove-section=.note.ABI-tag
#upx -9 --lzma roboeye
