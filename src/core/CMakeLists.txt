project(core)

set (CMAKE_CXX_STANDARD 20)
add_library(xhfr_core STATIC
    debug.hpp
    debug.cpp
)

#target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}../../external/spdlog/include)
target_link_libraries(xhfr_core spdlog)
