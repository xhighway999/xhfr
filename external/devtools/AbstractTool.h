#ifndef ABSTRACTTOOL_H
#define ABSTRACTTOOL_H
#include <imgui.h>



class AbstractTool
{
public:
    virtual const char * const getName() const noexcept;
    void run();
    void init();
protected:
    virtual void runImpl();
    virtual void initImpl();
};

#endif // ABSTRACTTOOL_H
