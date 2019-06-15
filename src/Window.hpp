#ifndef CORE_WINDOW_H
#define CORE_WINDOW_H
#include "WindowManagerBase.hpp"

namespace core {

class Window
{
    friend class WindowManagerBase;
public:

    Window();
    virtual void onDraw() = 0;
    virtual ~Window();
private:
    bool visible = true;

};

}

#endif // CORE_WINDOW_H
