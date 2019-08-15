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
#include "gui/gl/Backend.hpp"

namespace xhfr {
int init(const char* appName);
int main();
// All the evil globals that are required
extern Dockspace dockspace;

}  // namespace xhfr
