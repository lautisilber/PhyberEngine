#include "phyber/renderer_2d.h"
#include "phyber/common_2d.h"
#include "phyber/math.h"

#include <string.h>

using namespace Phyber;

color_precision_t _buffer_2d[2][PHYBER_ENGINE_RENDERER_2D_RESOLUTION_WIDTH][PHYBER_ENGINE_RENDERER_2D_RESOLUTION_HEIGHT][4];

Renderer2d::Renderer2d() {
    memset(gos_active, 0, PHYBER_ENGINE_RENDERER_2D_MAX_GAME_OBJECTS * sizeof(bool));
}

GameObject2d *Renderer2d::create_game_object() {
    for (
        bool *active_ptr = gos_active;
        active_ptr - gos_active < PHYBER_ENGINE_RENDERER_2D_MAX_GAME_OBJECTS;
        active_ptr++
    ) {
        if (!(*active_ptr)) {
            GameObject2d *go = &gos[active_ptr - gos_active];
            memset(go, 0, sizeof(GameObject2d));
            return go;
        }
    }
    return nullptr;
}

GameObject2d *Renderer2d::get_game_object(size_t n) {
    if (
        n >= PHYBER_ENGINE_RENDERER_2D_MAX_GAME_OBJECTS ||
        !gos_active[n]
    ) {
        return nullptr;
    }
    return &gos[n];
}

bool Renderer2d::delete_game_object(size_t n) {
    if (
        n >= PHYBER_ENGINE_RENDERER_2D_MAX_GAME_OBJECTS ||
        !gos_active[n]
    ) {
        return false;
    }
    gos_active[n] = 0;
    return true;
}

bool Renderer2d::delete_game_object(GameObject2d *ptr) {
    if (ptr < gos) return false;
    return delete_game_object(ptr - gos);
}

void Renderer2d::clear_buffer(buffer_t buffer, size_t width, size_t height) {
    memset(buffer, 0, width * height * 4 * sizeof(color_precision_t));
}

void Renderer2d::fill_buffer(buffer_t buffer, size_t width, size_t height, color_precision_t r, color_precision_t g, color_precision_t b, color_precision_t a) {
    for (size_t r = 0; r < width; ++r) {
        for (size_t c = 0; c < height; ++c) {
            color_precision_t *color = buffer[r][c];
            color[0] = r;
            color[1] = g;
            color[2] = b;
            color[3] = a;
        }
    }
}

void Renderer2d::render(Renderer2d::buffer_t buffer, size_t width, size_t height) {

}

void Renderer2d::clear_buffer() {
    memset(_buffer_2d[buffer_side], 0, PHYBER_ENGINE_RENDERER_2D_RESOLUTION_WIDTH * PHYBER_ENGINE_RENDERER_2D_RESOLUTION_HEIGHT * 4 * sizeof(color_precision_t));
}

void Renderer2d::fill_buffer(color_precision_t r, color_precision_t g, color_precision_t b, color_precision_t a) {
    for (size_t r = 0; r < PHYBER_ENGINE_RENDERER_2D_RESOLUTION_WIDTH; ++r) {
        for (size_t c = 0; c < PHYBER_ENGINE_RENDERER_2D_RESOLUTION_HEIGHT; ++c) {
            _buffer_2d[buffer_side][r][c][0] = r;
            _buffer_2d[buffer_side][r][c][1] = g;
            _buffer_2d[buffer_side][r][c][2] = b;
            _buffer_2d[buffer_side][r][c][3] = a;
        }
    }
}
