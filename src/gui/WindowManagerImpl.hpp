#ifndef CORE_WINDOWMANAGERIMPL_H
#define CORE_WINDOWMANAGERIMPL_H

#include <vector>

#include "WindowManagerBase.hpp"
#include "Window.hpp"

#include "imgui.h"

namespace core {

/**
 * @todo write docs
 */
class WindowManagerImpl : public WindowManagerBase
{
    public:
    WindowManagerImpl() {};
    virtual void addWindow(Window* window) override;
    virtual void manageWindows() override;
    virtual ~WindowManagerImpl() {}
    private:
    std::vector<Window*> windows;
};

}

#endif // CORE_WINDOWMANAGERIMPL_H
