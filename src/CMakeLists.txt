project(roboeye)

add_executable(roboeye main.cpp)
target_link_libraries(roboeye imgui imgui_impl glfw glad)

install(TARGETS roboeye RUNTIME DESTINATION bin)

