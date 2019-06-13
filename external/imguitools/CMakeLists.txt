project(imguitools)
cmake_minimum_required(VERSION 2.6)

option(IT_USE_STB "Use STB" ON)


add_library(imguitools STATIC
    Image.h
    Image.cpp
)

if($IT_USE_STB)
    target_compile_definitions(PUBLIC IT_USE_STB)
endif()

target_include_directories(imguitools PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )

target_link_libraries(imguitools imgui)

