#pragma once

#include "fs/fs.hpp"
#include "gui/Dockspace.hpp"
#include "gui/Fonts.hpp"
#include "gui/Image.hpp"
#include "gui/Widgets.hpp"
#include "gui/Window.hpp"
#include "gui/WindowManagerBase.hpp"
#include "gui/WindowManagerImpl.hpp"
#include "gui/backends/Backend.hpp"

#include <iostream>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
void emscripten_main_loop(void* arg);
#endif

namespace xhfr {
int init(int argc, char* argv[], const char* appName, int w = 800, int h = 600);
int main();
void new_frame();
void shutdown();
// All the evil globals that are required
extern Dockspace dockspace;
extern xhfr::WindowManagerBase* wm;
}  // namespace xhfr
