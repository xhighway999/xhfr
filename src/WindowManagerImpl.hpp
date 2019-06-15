#ifndef CORE_WINDOWMANAGERIMPL_H
#define CORE_WINDOWMANAGERIMPL_H

#include <vector>

#include "WindowManagerBase.hpp"
#include "Window.hpp"

namespace core {

/**
 * @todo write docs
 */
class WindowManagerImpl :  WindowManagerBase
{
    public:
    virtual void addWindow(Window* window) override;
    virtual void manageWindows() override;
    private:
    std::vector<Window*> windows;
};

}

#endif // CORE_WINDOWMANAGERIMPL_H
