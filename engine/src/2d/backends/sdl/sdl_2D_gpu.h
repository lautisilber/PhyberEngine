#ifndef BACKEND_SDL_RENDERER_2D_GPU_H
#define BACKEND_SDL_RENDERER_2D_GPU_H

#include "phyber/2d/renderer.h"

namespace Phyber {
namespace Renderer2D {
namespace GPU {
namespace SDL {
    extern void init(unsigned int width, unsigned int height);
    extern bool draw();
    extern float dt();
    extern void destroy();
    extern void fill(color_precision_t color);
}
}
}
}

#endif /* BACKEND_SDL_RENDERER_2D_GPU_H */
