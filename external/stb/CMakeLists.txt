project(stb)
cmake_minimum_required(VERSION 3.14.5)


add_library(stb STATIC
    stb.cpp
    stb/stb_vorbis.c
)


macro(GenOption OptionName)
    option(${OptionName} ${OptionName} On)
    if(${OptionName})
        target_compile_definitions(stb PRIVATE ${OptionName})
    endif()
endmacro(GenOption)

#GenOption(STB_IMAGE_WRITE_IMPLEMENTATION)
#GenOption(STB_IMAGE_IMPLEMENTATION)
#GenOption(STB_LEAKCHECK_IMPLEMENTATION)

target_include_directories(stb PUBLIC stb)
