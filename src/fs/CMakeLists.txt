project(fs)

set (CMAKE_CXX_STANDARD 17)
add_library(fs STATIC
    fs.hpp
    fs.cpp
    File.hpp
    File.cpp
)
#manually include physfs since the tharget does not
target_include_directories(fs PUBLIC "../../external/physfs/src/")
target_link_libraries(fs physfs-static core)

