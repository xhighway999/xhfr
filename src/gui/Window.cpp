#include "Window.hpp"

xhfr::Window::Window() {
  xhfr::wm->addWindow(this);
}

const std::string &xhfr::Window::getTitle() {
  return windowTitle;
}

void xhfr::Window::setTitle(const std::string &title) {
  windowTitle = title;
}

bool xhfr::Window::getVisible() {
  return visible;
}

void xhfr::Window::setVisible(bool vis) {
  visible = vis;
}

const ImGuiWindowFlags &xhfr::Window::getFlags() {
  return windowFlags;
}

void xhfr::Window::setFlag(ImGuiWindowFlags flag, bool enabled) {
  if(enabled)
    windowFlags |= flag;
  else
    windowFlags = windowFlags & ~flag;
}
