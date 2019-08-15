#ifndef CORE_WINDOW_H
#define CORE_WINDOW_H

#include "WindowManagerBase.hpp"
#include "imgui.h"

#include <string>

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
