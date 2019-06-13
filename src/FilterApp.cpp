#include "FilterApp.h"

void FilterApp::OnRun()
{
    if(ImGui::Begin("FilterApp"))
    {
        if(ImGui::Button("Test"))
        {
            sol::state lua;
            int x = 0;
            lua.set_function("beep", [&x]{ ++x; });
            lua.script("beep()");
            assert(x == 0);
        }
    ImGui::End();
    }
}
