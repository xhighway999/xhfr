#include "Window.hpp"

using namespace core;

Window::Window()
{
    core::wm->addWindow(this);
}

Window::~Window()
{

}
