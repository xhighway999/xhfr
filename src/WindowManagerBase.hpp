#ifndef CORE_WINDOWMANAGER_H
#define CORE_WINDOWMANAGER_H



namespace core {
class Window;
class WindowManagerBase
{
public:
    virtual void addWindow(Window* window);
    virtual void manageWindows();

};
extern WindowManagerBase* wm;
}

#endif // CORE_WINDOWMANAGER_H
