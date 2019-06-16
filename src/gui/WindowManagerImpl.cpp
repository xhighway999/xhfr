#include "WindowManagerImpl.hpp"

using namespace core;

void core::WindowManagerImpl::addWindow(core::Window* window)
{
    windows.push_back(window);
}

void core::WindowManagerImpl::manageWindows()
{
    for(Window* window : windows)
    {
        if(!window->getVisible())
            continue;
        
        ImGui::Begin(window->getTitle().c_str());
        window->onDraw();
        ImGui::End();
    }
}

