project(binary)

#add_subdirectory(gui)



add_executable(binary 
    main.cpp
    FilterApp.cpp)
target_link_libraries(binary dl sol2 imgui imgui_impl glfw glad stb ${CMAKE_CURRENT_SOURCE_DIR}/../external/luajit/src/libluajit.a)
target_include_directories(binary PUBLIC ../external/luajit/src/)
if(${TinyMode})
    #run upx and strip after build
    add_custom_command(
    OUTPUT binary-tiny
    COMMAND strip -S --strip-unneeded --remove-section=.note.gnu.gold-version --remove-section=.comment --remove-section=.note --remove-section=.note.gnu.build-id --remove-section=.note.ABI-tag -s -R .comment -R .gnu.version -o binary-tiny binary
    COMMAND upx -9 --lzma binary-tiny
    DEPENDS binary
    COMMENT "Stamping the license"
    VERBATIM
    )
    add_custom_target(
    TinyMode ALL
    DEPENDS binary-tiny
    )
endif()


if(${DevMode})
    target_compile_definitions(binary PUBLIC DEV)
    #Link the dev tools dependency
    target_link_libraries(binary devtools)
endif()
