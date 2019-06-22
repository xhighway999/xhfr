#ifndef CORE_WINDOWMANAGER_H
#define CORE_WINDOWMANAGER_H

namespace core {
class Window;
class WindowManagerBase {
public:
  WindowManagerBase()                    = default;
  virtual void addWindow(Window *window) = 0;
  virtual void manageWindows()           = 0;
  virtual ~WindowManagerBase() {}
};
extern WindowManagerBase *wm;
} // namespace core

#endif // CORE_WINDOWMANAGER_H
