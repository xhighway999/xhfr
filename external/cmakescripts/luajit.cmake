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

add_custom_target(
    luajit-static
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/luajit/src/libluajit.a
)
add_library(luajit SHARED IMPORTED GLOBAL)
target_include_directories(luajit SYSTEM INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/luajit/src)
set_target_properties(luajit PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/luajit/src/libluajit.a)
add_dependencies(luajit luajit-static)
