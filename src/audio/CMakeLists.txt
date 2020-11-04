project(xhfr_audio)

set (CMAKE_CXX_STANDARD 17)
add_library(xhfr_audio STATIC
    Player.hpp
    Player.cpp
    Recorder.hpp
    Recorder.cpp
)
#manually include physfs since the tharget does not
target_link_libraries(xhfr_audio PUBLIC wave xhfr_core SDL2-static)

