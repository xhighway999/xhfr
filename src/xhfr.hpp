#pragma once

#define SDL_MAIN_HANDLED
#include "core/ApplicationSettings.hpp"
#include "core/debug.hpp"
#include "fs/fs.hpp"
#include "gui/Dockspace.hpp"
#include "gui/Fonts.hpp"
#include "gui/Image.hpp"
#include "gui/Widgets.hpp"
#include "gui/Window.hpp"
#include "gui/WindowManagerBase.hpp"
#include "gui/WindowManagerImpl.hpp"
#include "gui/backends/Backend.hpp"

#include <functional>
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
void addUserFunction(const std::function<void()> func);
// All the evil globals that are required
extern Dockspace dockspace;
extern xhfr::WindowManagerBase* wm;
extern std::vector<std::function<void()>> userOnFrameFunctions;
extern debug dbg;
}  // namespace xhfr
