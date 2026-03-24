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
    extern bool render();
    extern void destroy();
}

// class Renderer2D {
// private:
//     bool buffer_side = false;
//     GameObject2D gos[PHYBER_ENGINE_RENDERER_2D_MAX_GAME_OBJECTS];
//     bool gos_active[PHYBER_ENGINE_RENDERER_2D_MAX_GAME_OBJECTS];

// public:
//     typedef color_precision_t* buffer_t;
//     Renderer2D();

//     GameObject2D *create_game_object();
//     GameObject2D *get_game_object(size_t n);
//     bool delete_game_object(size_t n);
//     bool delete_game_object(GameObject2D *ptr);

//     void clear_buffer(buffer_t buffer, size_t width, size_t height);
//     void fill_buffer(buffer_t buffer, size_t width, size_t height, color_precision_t r, color_precision_t g, color_precision_t b, color_precision_t a);
//     void render(buffer_t buffer, size_t width, size_t height);
//     #ifndef PHYBER_ENGINE_NO_2D_DEFAULT_BUFFER
//     void clear_buffer();
//     void fill_buffer(color_precision_t r, color_precision_t g, color_precision_t b, color_precision_t a);
//     void render();
//     #endif
// };

}

#endif /* PHYBER_ENGINE_RENDERER_2D_H */
