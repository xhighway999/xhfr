#ifndef XHFR_BACKEND_KEYCODES
#define XHFR_BACKEND_KEYCODES

#include "SDL_scancode.h"

#define SDL_SCANCODE_ENTER SDL_SCANCODE_RETURN

#define XHFR_KEY(key) (SDL_Scancode::SDL_SCANCODE_##key)

#endif
