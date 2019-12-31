#include "WindowManagerImpl.hpp"

void xhfr::WindowManagerImpl::addWindow(xhfr::Window* window) {
  windows.push_back(window);
}

void xhfr::WindowManagerImpl::manageWindows() {
  if (mainMenuBarUsed) {
    mainMenuBarFunction();
  }

  for (auto windowe = windows.begin(); windowe != windows.end(); ++windowe) {
    Window* window = *windowe;
    if (!window->getVisible())
      continue;
    bool close_pressed = true;
    if (ImGui::Begin(window->getTitle().c_str(), &close_pressed,
                     window->getFlags())) {
      if (!close_pressed) {
        auto it =
            windows.erase(std::remove(windows.begin(), windows.end(), window));
        it--;
        windowe = it;
        window->onClosePressed();
      }
      window->onDraw();
    }
    ImGui::End();
  }
}

void xhfr::WindowManagerImpl::setMainMenuBarFunction(
    std::function<void()> menuBarFunction) {
  mainMenuBarFunction = menuBarFunction;
  mainMenuBarUsed = true;
}

bool xhfr::WindowManagerImpl::MainMenuBarUsed() {
  return mainMenuBarUsed;
}
