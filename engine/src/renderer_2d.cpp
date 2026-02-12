#include "phyber/renderer_2d.h"
#include "phyber/common_2d.h"
#include "phyber/math.h"

#include <string.h>

const Phyber2DGameObject *_gos[PHYBER_ENGINE_RENDERER_2D_MAX_GAME_OBJECTS];
size_t _n_gos = 0;

// rgba
uint8_t _frame_buffer[PHYBER_ENGINE_RESOLUTION_PX_WIDTH * PHYBER_ENGINE_RESOLUTION_PX_HEIGHT][4];
float _z_buffer[PHYBER_ENGINE_RESOLUTION_PX_WIDTH * PHYBER_ENGINE_RESOLUTION_PX_HEIGHT];

bool phyber_add_game_object_to_stack(const Phyber2DGameObject *go) {
    if (_n_gos >= PHYBER_ENGINE_RENDERER_2D_MAX_GAME_OBJECTS - 1) {
        // Can't add more sprites!
        return false;
    }

    _gos[_n_gos++] = go;
    return true;
}

bool phyber_remove_game_object_from_stack(const Phyber2DGameObject *go) {
    for (size_t idx_to_remove = 0; idx_to_remove < PHYBER_ENGINE_RENDERER_2D_MAX_GAME_OBJECTS; ++idx_to_remove) {
        if (_gos[idx_to_remove] != go) { continue; }

        // found go in stack
        if (idx_to_remove == PHYBER_ENGINE_RENDERER_2D_MAX_GAME_OBJECTS-1) {
            _gos[PHYBER_ENGINE_RENDERER_2D_MAX_GAME_OBJECTS-1] = 0;
        } else {
            memmove(_gos + idx_to_remove, _gos + idx_to_remove + 1, (_n_gos - idx_to_remove) - 1);
        }
        --idx_to_remove;
        return true;
    }
    // didn't find any coincidence
    return false;
}

void _render_single_go(const Phyber2DGameObject *go) {
    const PhyberSprite *sprite = &go->sprite;
    const PhyberTransform2d *transform = &go->transform;

    const uint16_t sprite_width = sprite->width;
    const uint16_t sprite_height = sprite->height;
    const float sprite_center_x = sprite->center_x;
    const float sprite_center_y = sprite->center_y;

    // render area = ra
    size_t ra_top = 0;
    size_t ra_left = 0;
    size_t ra_bottom = sprite_height;
    size_t ra_right = sprite_width;

    // apply scale
    // transform->scale
    phyber_vector_2d_scale(PhyberVec2 *vec, const PhyberVec2 *scale)
}

void phyber_render_2d() {
    for (size_t i = 0; i < _n_gos; ++i) {

    }
}
