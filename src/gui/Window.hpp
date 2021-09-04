#ifndef CORE_WINDOW_H
#define CORE_WINDOW_H

#include <string>

#include <map>
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

  void setColor(ImGuiCol colorName, ImVec4 color);

  const ImGuiWindowFlags& getFlags();

  void destroy();
  virtual void onDrop(DropEvent) {}

  void setFlag(ImGuiWindowFlags flag, bool enabled = true);
  void hideCloseButton(bool newHideCloseButton);

 protected:
  ImGuiWindowFlags windowFlags = 0;

 private:
  bool destroyWindow = false;
  bool visible = false;
  bool hideCloseButtonState = false;
  std::string windowTitle = "";
  std::map<ImGuiCol, ImVec4> styleSheet;
};

}  // namespace xhfr

#endif  // CORE_WINDOW_H
