#ifndef PHYBER_ENGINE_RENDERER_2D_H
#define PHYBER_ENGINE_RENDERER_2D_H

#include "phyber/2d/common.h"
#include "phyber/defs/global_defines.h"

#ifndef PHYBER_ENGINE_RENDERER_2D_MAX_GAME_OBJECTS
#define PHYBER_ENGINE_RENDERER_2D_MAX_GAME_OBJECTS 256
#endif

namespace Phyber {

namespace Renderer2d_cpu {
    extern color_precision_t *buffer;
    extern bool init(unsigned int width, unsigned int height);
    extern bool render();
    extern void destroy();
}

// class Renderer2d {
// private:
//     bool buffer_side = false;
//     GameObject2d gos[PHYBER_ENGINE_RENDERER_2D_MAX_GAME_OBJECTS];
//     bool gos_active[PHYBER_ENGINE_RENDERER_2D_MAX_GAME_OBJECTS];

// public:
//     typedef color_precision_t* buffer_t;
//     Renderer2d();

//     GameObject2d *create_game_object();
//     GameObject2d *get_game_object(size_t n);
//     bool delete_game_object(size_t n);
//     bool delete_game_object(GameObject2d *ptr);

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
