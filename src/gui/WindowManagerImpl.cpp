#include "WindowManagerImpl.hpp"

void xhfr::WindowManagerImpl::addWindow(xhfr::Window* window) {
  windows.push_back(window);
}

bool xhfr::WindowManagerImpl::hasWindow(xhfr::Window* window) {
  for (const auto* w : windows) {
    if (w == window) {
      return true;
    }
  }
  return false;
}

void xhfr::WindowManagerImpl::manageWindows() {
  if (mainMenuBarUsed) {
    mainMenuBarFunction();
  }

  // this is a little weird to account for size changes while in loop
  size_t i = 0, totalWindows = windows.size();
  for (i = 0; i != totalWindows; i++) {
    Window* window = windows[i];
    if (!window->getVisible())
      continue;
    bool open = true;
    if (ImGui::Begin(window->getTitle().c_str(), &open, window->getFlags())) {
      if (!open) {
        window->destroyWindow = true;
      }
      window->onDraw();
    }
    ImGui::End();
  }

  // handle window destruction
  std::remove_if(windows.begin(), windows.end(), [](Window* w) {
    if (w->destroyWindow) {
      w->onClosePressed();
      return true;
    }
    return false;
  });
}

void xhfr::WindowManagerImpl::destroyWindow(xhfr::Window* window) {
  window->destroy();
  // windows.erase(std::remove(windows.begin(), windows.end(), window));
}

void xhfr::WindowManagerImpl::setMainMenuBarFunction(
    std::function<void()> menuBarFunction) {
  mainMenuBarFunction = menuBarFunction;
  mainMenuBarUsed = true;
}

bool xhfr::WindowManagerImpl::MainMenuBarUsed() {
  return mainMenuBarUsed;
}
