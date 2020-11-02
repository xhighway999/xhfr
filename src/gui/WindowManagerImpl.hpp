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
  virtual void destroyWindow(Window* window) override;
  virtual void setMainMenuBarFunction(
      std::function<void()> menuBarFunction) override;
  virtual bool MainMenuBarUsed() override;
  virtual ~WindowManagerImpl() {}
  virtual std::function<void(DropEvent)> getDropEventCallback() override;

 private:
  std::vector<Window*> windows;
  std::function<void()> mainMenuBarFunction;
  std::function<void(DropEvent)> dropEventCallback;
  bool mainMenuBarUsed = false;
};

}  // namespace xhfr

#endif  // CORE_WINDOWMANAGERIMPL_H
