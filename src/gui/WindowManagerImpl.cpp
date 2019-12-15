#include "WindowManagerImpl.hpp"

void xhfr::WindowManagerImpl::addWindow(xhfr::Window* window) {
  windows.push_back(window);
}

void xhfr::WindowManagerImpl::manageWindows() {
  if (mainMenuBarUsed) {
    mainMenuBarFunction();
  }
  for (Window* window : windows) {
    if (!window->getVisible())
      continue;

    ImGui::Begin(window->getTitle().c_str(), NULL, window->getFlags());
    window->onDraw();
    ImGui::End();
  }
}

void xhfr::WindowManagerImpl::setMainMenuBarFunction(
    std::function<void()> menuBarFunction) {
  mainMenuBarFunction = menuBarFunction;
  mainMenuBarUsed = true;
}
