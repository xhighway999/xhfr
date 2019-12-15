#ifndef CORE_WINDOWMANAGER_H
#define CORE_WINDOWMANAGER_H

#include <functional>

namespace xhfr {
class Window;
class WindowManagerBase {
 public:
  WindowManagerBase() = default;
  virtual void addWindow(Window* window) = 0;
  virtual void manageWindows() = 0;
  virtual void setMainMenuBarFunction(
      std::function<void()> menuBarFunction) = 0;
  virtual ~WindowManagerBase() {}
};
extern WindowManagerBase* wm;
}  // namespace xhfr

#endif  // CORE_WINDOWMANAGER_H
