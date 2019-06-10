#ifndef FILTERAPP_H
#define FILTERAPP_H

#include <string>
#include <sol2/include/sol/sol.hpp>
#include "imgui/imgui.h"

/**
 * @todo write docs
 */
class FilterApp
{
public:
    void OnRun();
private:
    std::string imgPath = "../img.png";
};

#endif // FILTERAPP_H
