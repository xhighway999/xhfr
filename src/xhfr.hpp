#pragma once

// dear imgui: standalone example application for GLFW + OpenGL 3, using
// programmable pipeline If you are new to dear imgui, see examples/README.txt
// and documentation at the top of imgui.cpp. (GLFW is a cross-platform general
// purpose library for handling windows, inputs, OpenGL/Vulkan graphics context
// creation, etc.)

#include "gui/Dockspace.hpp"
#include "gui/Image.hpp"
#include "gui/Widgets.hpp"
#include "gui/Window.hpp"
#include "gui/WindowManagerBase.hpp"
#include "gui/WindowManagerImpl.hpp"
#include "gui/backends/Backend.hpp"

#include "fs/fs.hpp"

namespace xhfr {
int init(int argc, char* argv[], const char* appName, int w = 800, int h = 600);
int main();
void new_frame();
void shutdown();
// All the evil globals that are required
extern Dockspace dockspace;

}  // namespace xhfr
