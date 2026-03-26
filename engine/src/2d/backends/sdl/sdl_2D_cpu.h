#ifndef BACKEND_SDL_RENDERER_2D_CPU_h
#define BACKEND_SDL_RENDERER_2D_CPU_h

#include "phyber/2d/renderer.h"

namespace Phyber {
namespace Renderer2D_cpu {
namespace SDL {
    extern void init(color_precision_t *buffer, unsigned int width, unsigned int height);
    extern bool draw(color_precision_t *buffer, unsigned int width, unsigned int height);
    extern float dt();
    extern void destroy();
}
}
}

#endif /* BACKEND_SDL_RENDERER_2D_CPU_h */
