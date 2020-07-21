#ifndef CORE_WINDOW_H
#define CORE_WINDOW_H

#include <string>

#include "WindowManagerBase.hpp"
#include "imgui.h"

namespace xhfr {

class Window {
  friend class WindowManagerBase;
  friend class WindowManagerImpl;

 public:
  Window();
  virtual void onDraw() = 0;
  virtual ~Window();
  const std::string& getTitle();
  void setTitle(const std::string& title);
  void setVisible(bool vis);
  bool getVisible();
  virtual void onClosePressed() {}

  const ImGuiWindowFlags& getFlags();

  void destroy();

 protected:
  void setFlag(ImGuiWindowFlags flag, bool enabled = true);
  ImGuiWindowFlags windowFlags = 0;

 private:
  bool destroyWindow = false;
  bool visible = false;
  std::string windowTitle = "";
};

}  // namespace xhfr

#endif  // CORE_WINDOW_H
