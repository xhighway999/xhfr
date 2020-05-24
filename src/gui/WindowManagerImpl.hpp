#ifndef CORE_WINDOWMANAGERIMPL_H
#define CORE_WINDOWMANAGERIMPL_H

#include <vector>

#include "Window.hpp"
#include "WindowManagerBase.hpp"
#include "imgui.h"

namespace xhfr {

class WindowManagerImpl : public WindowManagerBase {
 public:
  WindowManagerImpl(){};
  virtual void addWindow(Window* window) override;
  virtual bool hasWindow(Window* window) override;
  virtual void manageWindows() override;
  virtual void setMainMenuBarFunction(
      std::function<void()> menuBarFunction) override;
  virtual bool MainMenuBarUsed() override;
  virtual ~WindowManagerImpl() {}

 private:
  std::vector<Window*> windows;
  std::function<void()> mainMenuBarFunction;
  bool mainMenuBarUsed = false;
};

}  // namespace xhfr

#endif  // CORE_WINDOWMANAGERIMPL_H
