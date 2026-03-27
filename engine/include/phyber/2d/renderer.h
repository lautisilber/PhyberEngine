#ifndef PHYBER_ENGINE_RENDERER_2D_H
#define PHYBER_ENGINE_RENDERER_2D_H

#include <stdint.h>
#include "common.h"
#include "phyber/2d/common.h"
#include "phyber/defs/global_defines.h"

#ifndef PHYBER_ENGINE_RENDERER_2D_MAX_GAME_OBJECTS
#define PHYBER_ENGINE_RENDERER_2D_MAX_GAME_OBJECTS 256
#endif

namespace Phyber {
namespace Renderer2D {

    typedef void (*init_backend_t)(color_precision_t *buffer, unsigned int width, unsigned int height);
    typedef bool (*draw_backend_t)(color_precision_t *buffer, unsigned int width, unsigned int height);
    typedef float (*dt_backend_t)(void); // in s
    typedef void (*destroy_backend_t)(void);

    extern bool add_go(GameObject2D &go);
    extern bool remove_go(GameObject2D &go);

namespace CPU {

    extern color_precision_t *pixel_buffer;
    extern z_buffer_precision_t *z_buffer;

    enum RasterizationQuality : uint8_t {
        SUBPIXEL_PRECISION, ANTI_ALIASING
    };

    extern void init(unsigned int width, unsigned int height, RasterizationQuality rasterization_quality=SUBPIXEL_PRECISION, init_backend_t init_f=nullptr, draw_backend_t draw_f=nullptr, dt_backend_t dt_f=nullptr, destroy_backend_t destroy_f=nullptr);
    extern float dt();
    extern bool render(const Phyber::Camera2D &camera);
    extern bool draw();
    extern void destroy();
    extern void fill(color_precision_t color);
}

namespace GPU {

    enum RasterizationQuality : uint8_t {
        SUBPIXEL_PRECISION, ANTI_ALIASING
    };

    extern void init(unsigned int width, unsigned int height, RasterizationQuality rasterization_quality=SUBPIXEL_PRECISION, init_backend_t init_f=nullptr, draw_backend_t draw_f=nullptr, dt_backend_t dt_f=nullptr, destroy_backend_t destroy_f=nullptr);
    extern float dt();
    extern bool render(const Phyber::Camera2D &camera);
    extern bool draw();
    extern void destroy();
    extern void fill(color_precision_t color);

}
}
}

#endif /* PHYBER_ENGINE_RENDERER_2D_H */
