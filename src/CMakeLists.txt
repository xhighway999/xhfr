project(roboeye)

add_subdirectory(gui)


add_executable(roboeye 
    main.cpp
    FilterApp.cpp)
target_link_libraries(roboeye imgui imgui_impl glfw glad stb)

install(TARGETS roboeye RUNTIME DESTINATION bin)

