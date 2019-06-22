#ifndef CORE_WINDOW_H
#define CORE_WINDOW_H

#include <string>

#include "imgui.h"

#include "WindowManagerBase.hpp"

namespace core {

class Window {
  friend class WindowManagerBase;

public:
  Window();
  virtual void onDraw() = 0;
  virtual ~Window();
  const std::string &getTitle();
  void setTitle(const std::string &title);
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

} // namespace core

#endif // CORE_WINDOW_H
