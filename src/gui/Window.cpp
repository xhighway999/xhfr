#include "Window.hpp"

using namespace core;

Window::Window() {
  core::wm->addWindow(this);
}

Window::~Window() {}

const std::string &core::Window::getTitle() {
  return windowTitle;
}

void core::Window::setTitle(const std::string &title) {
  windowTitle = title;
}

bool core::Window::getVisible() {
  return visible;
}

void core::Window::setVisible(bool vis) {
  visible = vis;
}

const ImGuiWindowFlags & core::Window::getFlags()
{
  return windowFlags;
}

void core::Window::setFlag(ImGuiWindowFlags flag, bool enabled)
{
  if(enabled)
    windowFlags |= flag;
  else
    windowFlags = windowFlags & ~flag; 
}

