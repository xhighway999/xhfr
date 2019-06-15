#include "WindowManagerImpl.hpp"

using namespace core;

void core::WindowManagerImpl::addWindow(core::Window* window)
{
    windows.push_back(window);
}

void core::WindowManagerImpl::manageWindows()
{
    for(auto* window : windows)
    {
        window->onDraw();
    }
}

