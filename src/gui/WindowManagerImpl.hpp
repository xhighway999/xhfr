#ifndef CORE_WINDOWMANAGERIMPL_H
#define CORE_WINDOWMANAGERIMPL_H

#include "Window.hpp"
#include "WindowManagerBase.hpp"
#include "imgui.h"

#include <vector>

namespace xhfr {

class WindowManagerImpl : public WindowManagerBase {
public:
  WindowManagerImpl(){};
  virtual void addWindow(Window *window) override;
  virtual void manageWindows() override;
  virtual ~WindowManagerImpl() {}

private:
  std::vector<Window *> windows;
};

} // namespace xhfr

#endif // CORE_WINDOWMANAGERIMPL_H
