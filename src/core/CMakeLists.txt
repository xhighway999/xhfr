project(core)

set (CMAKE_CXX_STANDARD 20)
add_library(xhfr_core STATIC
    debug.hpp
    debug.cpp
    ApplicationSettings.hpp
    ApplicationSettings.cpp
)



#manually include physfs since the tharget does not
target_include_directories(xhfr_core PUBLIC "../../external/physfs/src/")

#target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}../../external/spdlog/include)
target_link_libraries(xhfr_core PUBLIC physfs-static spdlog nlohmann_json::nlohmann_json)
