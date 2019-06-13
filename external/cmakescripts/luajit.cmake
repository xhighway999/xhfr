#include(ExternalProject)
#find_program(MAKE_EXE NAMES gmake nmake make)
#ExternalProject_Add(luajit
#SOURCE_DIR        ${CMAKE_CURRENT_SOURCE_DIR}/luajit
#CONFIGURE_COMMAND "ls -l"
#BUILD_COMMAND     ${MAKE_EXE})

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/luajit/src/libluajit.a
                   COMMAND make amalg
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/luajit
)

message(${CMAKE_CURRENT_SOURCE_DIR}/luajit/src/libluajit.a)

add_custom_target(
    luajit-static
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/luajit/src/libluajit.a
)
