#ifndef PHYBER_ENGINE_RENDERER_2D_H
#define PHYBER_ENGINE_RENDERER_2D_H

#include "phyber/2d/common.h"
#include "phyber/defs/global_defines.h"

#ifndef PHYBER_ENGINE_RENDERER_2D_MAX_GAME_OBJECTS
#define PHYBER_ENGINE_RENDERER_2D_MAX_GAME_OBJECTS 256
#endif

namespace Phyber {
namespace Renderer2D_cpu {

    typedef void (*init_backend_t)(color_precision_t *buffer, unsigned int width, unsigned int height);
    typedef bool (*draw_backend_t)(color_precision_t *buffer, unsigned int width, unsigned int height);
    typedef float (*dt_backend_t)(void); // in s
    typedef void (*destroy_backend_t)(void);

    extern color_precision_t *buffer;
    extern void init(unsigned int width, unsigned int height, init_backend_t init_f=nullptr, draw_backend_t draw_f=nullptr, dt_backend_t dt_f=nullptr, destroy_backend_t destroy_f=nullptr);
    extern float dt();
    extern bool render();
    extern void destroy();

}
}

#endif /* PHYBER_ENGINE_RENDERER_2D_H */
