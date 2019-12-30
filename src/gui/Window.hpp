#ifndef CORE_WINDOW_H
#define CORE_WINDOW_H

#include <string>

#include "WindowManagerBase.hpp"
#include "imgui.h"

namespace xhfr {

class Window {
  friend class WindowManagerBase;

 public:
  Window();
  virtual void onDraw() = 0;
  virtual ~Window() = default;
  const std::string& getTitle();
  void setTitle(const std::string& title);
  void setVisible(bool vis);
  bool getVisible();
  virtual void onClosePressed() {}

  const ImGuiWindowFlags& getFlags();

 protected:
  void setFlag(ImGuiWindowFlags flag, bool enabled = true);
  ImGuiWindowFlags windowFlags = 0;

 private:
  bool visible = false;
  std::string windowTitle = "";
};

}  // namespace xhfr

#endif  // CORE_WINDOW_H
