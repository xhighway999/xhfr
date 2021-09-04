#include "Window.hpp"

xhfr::Window::Window() {
  xhfr::wm->addWindow(this);
}

xhfr::Window::~Window() {}

const std::string& xhfr::Window::getTitle() {
  return windowTitle;
}

void xhfr::Window::setTitle(const std::string& title) {
  windowTitle = title;
}

bool xhfr::Window::getVisible() {
  return visible;
}

void xhfr::Window::setColor(ImGuiCol colorName, ImVec4 color) {
  styleSheet[colorName] = color;
}

void xhfr::Window::setVisible(bool vis) {
  if (!xhfr::wm->hasWindow(this) && vis) {
    xhfr::wm->addWindow(this);
  }
  visible = vis;
}

const ImGuiWindowFlags& xhfr::Window::getFlags() {
  return windowFlags;
}

void xhfr::Window::setFlag(ImGuiWindowFlags flag, bool enabled) {
  if (enabled)
    windowFlags |= flag;
  else
    windowFlags = windowFlags & ~flag;
}

void xhfr::Window::destroy() {
  destroyWindow = true;
}

void xhfr::Window::hideCloseButton(bool newHideCloseButton) {
  hideCloseButtonState = newHideCloseButton;
}
