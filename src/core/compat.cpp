#include "compat.hpp"
#ifdef __EMSCRIPTEN__
#include <emscripten.h>

void xhfr::openURL(const char* url) {

  EM_ASM(
    {
      var url = UTF8ToString($0);
      window.open(url);
    },
    url
  );
}
#else

#include "SDL2/SDL.h"
void xhfr::openURL(const char* url) {
  SDL_OpenURL(url);
}

#endif
