#include "phyber/renderer_2d.h"
#include "phyber/common_2d.h"
#include "phyber/math.h"

#include <cmath>
#include <stdexcept>
#include <string.h>

using namespace Phyber;

color_precision_t _buffer_2d[2][PHYBER_ENGINE_RENDERER_2D_RESOLUTION_WIDTH * PHYBER_ENGINE_RENDERER_2D_RESOLUTION_HEIGHT * 4];

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
            buffer[r * width + c + 0] = r;
            buffer[r * width + c + 1] = g;
            buffer[r * width + c + 2] = b;
            buffer[r * width + c + 3] = a;
        }
    }
}

static void _render_go(Renderer2d::buffer_t buffer, size_t width, size_t height, GameObject2d *go) {
    // first we need get a square that will fit the transformed sprite
    // -> get untransformed size
    Vec2 top_left(0,0);
    Vec2 bottom_right = go->sprite.size;
    Vec2 center = go->sprite.center;
    // -> translate to (0,0)
    top_left -= center;
    bottom_right -= center;
    // -> scale
    top_left.x *= go->transform.scale.x;
    top_left.y *= go->transform.scale.y;
    bottom_right.x *= go->transform.scale.x;
    bottom_right.y *= go->transform.scale.y;
    // -> rotate
    const float radians = radians_to_range(go->transform.rot);
    const Mat2x2 rotation = Mat2x2::rotation_matrix(radians);
    top_left *= rotation;
    top_left *= rotation;
    // -> get how big is the pixel region
    const int x_diff = ceilf(abs(bottom_right.x - top_left.x));
    const int y_diff = ceilf(abs(bottom_right.y - top_left.y));

    // from the final pixel positions, we sample from the original image
    // transformation is:
    // 1) pixel space -> sprite local space
    // 2) rotate
    // 3) scale
    // 4) translate
    // the inverse_transform does this in the inverse direction
    const Mat3x3 translate_inv({
        1, 0, -go->transform.pos.x,
        0, 1, -go->transform.pos.y,
        0, 0, 1
    });
    const Mat3x3 scale_inv(Vec3(-go->transform.scale.x, -go->transform.scale.y, 1));
    const Mat3x3 rotate_inv = Mat3x3::rotation_matrix_z(-radians);
    const Mat3x3 pixel2sprite_transform_inv = Mat3x3::translation_2d_matrix(&go->sprite.center);
    const Mat3x3 inverse_transform =
        translate_inv *
        scale_inv *
        rotate_inv *
        pixel2sprite_transform_inv;

    Vec3 pos(1,1,1);

    for (int x = 0; x < x_diff; ++x) {
        for (int y = 0; y < y_diff; ++y) {
            // set pos to the global final position of the pixel
            pos.x = x + go->transform.pos.x;
            pos.y = y + go->transform.pos.y;

            // inverse transform pos to pixel space
            pos *= inverse_transform;

            // sample the pixel in pixel space
            const int px_space_r = static_cast<int>(pos.x);
            const int px_space_c = static_cast<int>(pos.y);
            // sanity check
            if (px_space_r < 0 || px_space_r >= go->sprite.size.x) {
                throw std::runtime_error("Pixel sampling out of bounds (x)");
            } else if (px_space_c < 0 || px_space_r>= go->sprite.size.y) {
                throw std::runtime_error("Pixel sampling out of bounds (y)");
            }
            color_precision_t *pixel = &go->sprite.pixels[px_space_r * go->sprite.size.x + px_space_c]; // this is a color_precision_t[4]
        }
    }
}

void Renderer2d::render(Renderer2d::buffer_t buffer, size_t width, size_t height) {

}

void Renderer2d::clear_buffer() {
    clear_buffer(_buffer_2d[buffer_side], PHYBER_ENGINE_RENDERER_2D_RESOLUTION_WIDTH, PHYBER_ENGINE_RENDERER_2D_RESOLUTION_HEIGHT);
}

void Renderer2d::fill_buffer(color_precision_t r, color_precision_t g, color_precision_t b, color_precision_t a) {
    fill_buffer(_buffer_2d[buffer_side], PHYBER_ENGINE_RENDERER_2D_RESOLUTION_WIDTH, PHYBER_ENGINE_RENDERER_2D_RESOLUTION_HEIGHT, r, g, b, a);
}
