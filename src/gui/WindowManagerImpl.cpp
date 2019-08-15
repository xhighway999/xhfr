#include "WindowManagerImpl.hpp"

void xhfr::WindowManagerImpl::addWindow(xhfr::Window* window) {
  windows.push_back(window);
}

void xhfr::WindowManagerImpl::manageWindows() {
  for (Window* window : windows) {
    if (!window->getVisible())
      continue;

    ImGui::Begin(window->getTitle().c_str(), NULL, window->getFlags());
    window->onDraw();
    ImGui::End();
  }
}
