#ifndef FILTERAPP_H
#define FILTERAPP_H

#include <string>
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
