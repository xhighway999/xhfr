#ifndef DOCKSPACE_H
#define DOCKSPACE_H

#include <imgui.h>

namespace core {
class Dockspace {
public:
  Dockspace();
  ~Dockspace();
  void dockspaceStart();
  void dockspaceEnd();
  bool showDebugMenu = false;
};
} // namespace core

#endif // DOCKSPACE_H
