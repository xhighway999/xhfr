#ifndef DOCKSPACE_H
#define DOCKSPACE_H

#include <imgui.h>

namespace xhfr {
class Dockspace {
 public:
  Dockspace();
  void dockspaceStart();
  void dockspaceEnd();
  bool showDebugMenu = false;
  bool viewportHasWindowBar = true;
};
}  // namespace xhfr

#endif  // DOCKSPACE_H
