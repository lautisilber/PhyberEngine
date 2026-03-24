#include "phyber/2d/renderer.h"
#include "phyber/2d/common.h"
#include "phyber/logging.h"

#include <exception>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective

#include <SDL3/SDL.h>

#include <cmath>
#include <stdexcept>
#include <memory.h>
#include <string.h>
#include <vector>

color_precision_t *Phyber::Renderer2D_cpu::buffer = nullptr;
unsigned int g_width = 0, g_height = 0;

size_t sdl_buffer_pitch = 0;
SDL_Window* sdl_window = nullptr;
SDL_Renderer* sdl_renderer = nullptr;
SDL_Texture* sdl_texture = nullptr;
float sdl_dt_s = 1; // in s

void sdl_destroy() {

    SDL_DestroyTexture(sdl_texture);
    SDL_DestroyRenderer(sdl_renderer);
    SDL_DestroyWindow(sdl_window);
}

void sdl_init(color_precision_t *buffer, unsigned int width, unsigned int height) {
    // create a sdl_window
    sdl_window = SDL_CreateWindow("Hello, streaming sdl_texture!", width, height, 0);
    if (!sdl_window) {
        PHYBER_LOG_CRITICAL("Couldn't get sdl_window: %s", SDL_GetError());
        goto error;
    }

    // get sdl_renderer
    sdl_renderer = SDL_CreateRenderer(sdl_window, NULL);
    if (!sdl_renderer) {
        PHYBER_LOG_CRITICAL("Couldn't get sdl_renderer: %s", SDL_GetError());
        goto error;
    }

    // create sdl_texture
    sdl_texture = SDL_CreateTexture(
        sdl_renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        width,
        height
    );
    if (!sdl_texture) {
        PHYBER_LOG_CRITICAL("Couldn't create sdl_texture: %s", SDL_GetError());
        goto error;
    }

    return;

    error:
    sdl_destroy();
    exit(1);
}

bool sdl_draw(color_precision_t *buffer, unsigned int width, unsigned int height) {
    // update the sdl_texture
    size_t buffer_pitch = sizeof(color_precision_t) * width;
    if (!SDL_UpdateTexture(
        sdl_texture,                 // the sdl_texture to update.
        NULL,                    // an SDL_Rect structure representing the area to update, or NULL to update the entire sdl_texture.
        buffer,                  // the raw pixel data in the format of the sdl_texture.
        buffer_pitch // the number of bytes in a row of pixel data, including padding between lines.
    )) {
        PHYBER_LOG_ERROR("Couldn't update sdl_texture: ", SDL_GetError());
        return false;
    }

    // SDL_RenderClear(sdl_renderer);
    if (!SDL_RenderTexture(sdl_renderer, sdl_texture, NULL, NULL)) {
        PHYBER_LOG_ERROR("Couldn't render sdl_texture: ", SDL_GetError());
        return false;
    }
    if (!SDL_RenderPresent(sdl_renderer)) {
        PHYBER_LOG_ERROR("Couldn't present rendered sdl_texture: ", SDL_GetError());
        return false;
    }

    // update dt
    static uint64_t last_ticks = 0;
    uint64_t curr_ticks = SDL_GetTicks();
    sdl_dt_s = (curr_ticks - last_ticks) / 1000.0f;
    last_ticks = curr_ticks;

    return true;
}

float sdl_dt() {
    return sdl_dt_s;
}

Phyber::Renderer2D_cpu::init_backend_t b_init = nullptr;
Phyber::Renderer2D_cpu::draw_backend_t b_draw = nullptr;
Phyber::Renderer2D_cpu::dt_backend_t b_dt = nullptr;
Phyber::Renderer2D_cpu::destroy_backend_t b_destroy = nullptr;

void Phyber::Renderer2D_cpu::init(unsigned int width, unsigned int height, init_backend_t init_f, draw_backend_t draw_f, dt_backend_t dt_f, destroy_backend_t destroy_f) {
    if (
        init_f == nullptr ||
        draw_f == nullptr ||
        destroy_f == nullptr
    ) {
        if (!(
            init_f == nullptr &&
            draw_f == nullptr &&
            destroy_f == nullptr
        )) {
            throw std::runtime_error("If one backend function wasn't provided, then no backend function should be provided");
        }

        b_init = sdl_init;
        b_draw = sdl_draw;
        b_dt = sdl_dt;
        b_destroy = sdl_destroy;
    } else if (
        init_f != nullptr ||
        draw_f != nullptr ||
        destroy_f != nullptr
    ) {
        if (!(
            init_f != nullptr &&
            draw_f != nullptr &&
            destroy_f != nullptr
        )) {
            throw std::runtime_error("If one backend function was provided, then all backend functions should be provided");
        }

        b_init = init_f;
        b_draw = draw_f;
        b_dt = dt_f;
        b_destroy = destroy_f;
    }

    g_width = width;
    g_height = height;
    size_t buffer_pitch = sizeof(color_precision_t) * g_width;
    buffer = (color_precision_t*)malloc(buffer_pitch * g_height);
    if (!buffer) {
        PHYBER_LOG_CRITICAL("Coudln't allocate screen buffer");
        destroy();
        exit(1);
    }

    b_init(buffer, g_width, g_height);
}

bool Phyber::Renderer2D_cpu::render() {
    return b_draw(buffer, g_width, g_height);
}



void Phyber::Renderer2D_cpu::destroy() {
    if (buffer)
        free(buffer);

    b_destroy();
}

// color_precision_t _buffer_2d[2][PHYBER_ENGINE_RENDERER_2D_RESOLUTION_WIDTH * PHYBER_ENGINE_RENDERER_2D_RESOLUTION_HEIGHT * 4];

// Renderer2d::Renderer2d() {
//     memset(gos_active, 0, PHYBER_ENGINE_RENDERER_2D_MAX_GAME_OBJECTS * sizeof(bool));
// }

// GameObject2d *Renderer2d::create_game_object() {
//     for (
//         bool *active_ptr = gos_active;
//         active_ptr - gos_active < PHYBER_ENGINE_RENDERER_2D_MAX_GAME_OBJECTS;
//         active_ptr++
//     ) {
//         if (!(*active_ptr)) {
//             GameObject2d *go = &gos[active_ptr - gos_active];
//             memset(go, 0, sizeof(GameObject2d));
//             return go;
//         }
//     }
//     return nullptr;
// }

// GameObject2d *Renderer2d::get_game_object(size_t n) {
//     if (
//         n >= PHYBER_ENGINE_RENDERER_2D_MAX_GAME_OBJECTS ||
//         !gos_active[n]
//     ) {
//         return nullptr;
//     }
//     return &gos[n];
// }

// bool Renderer2d::delete_game_object(size_t n) {
//     if (
//         n >= PHYBER_ENGINE_RENDERER_2D_MAX_GAME_OBJECTS ||
//         !gos_active[n]
//     ) {
//         return false;
//     }
//     gos_active[n] = 0;
//     return true;
// }

// bool Renderer2d::delete_game_object(GameObject2d *ptr) {
//     if (ptr < gos) return false;
//     return delete_game_object(ptr - gos);
// }

// void Renderer2d::clear_buffer(buffer_t buffer, size_t width, size_t height) {
//     memset(buffer, 0, width * height * 4 * sizeof(color_precision_t));
// }

// void Renderer2d::fill_buffer(buffer_t buffer, size_t width, size_t height, color_precision_t r, color_precision_t g, color_precision_t b, color_precision_t a) {
//     for (size_t r = 0; r < width; ++r) {
//         for (size_t c = 0; c < height; ++c) {
//             buffer[r * width + c + 0] = r;
//             buffer[r * width + c + 1] = g;
//             buffer[r * width + c + 2] = b;
//             buffer[r * width + c + 3] = a;
//         }
//     }
// }

// static void _render_go(Renderer2d::buffer_t buffer, size_t width, size_t height, GameObject2d *go) {
//     // first we need get a square that will fit the transformed sprite
//     // -> get untransformed size
//     Vec2 top_left(0,0);
//     Vec2 bottom_right = go->sprite.size;
//     Vec2 center = go->sprite.center;
//     // -> translate to (0,0)
//     top_left -= center;
//     bottom_right -= center;
//     // -> scale
//     top_left.x *= go->transform.scale.x;
//     top_left.y *= go->transform.scale.y;
//     bottom_right.x *= go->transform.scale.x;
//     bottom_right.y *= go->transform.scale.y;
//     // -> rotate
//     const float radians = radians_to_range(go->transform.rot);
//     const Mat2x2 rotation = Mat2x2::rotation_matrix(radians);
//     top_left *= rotation;
//     top_left *= rotation;
//     // -> get how big is the pixel region
//     const int x_diff = ceilf(abs(bottom_right.x - top_left.x));
//     const int y_diff = ceilf(abs(bottom_right.y - top_left.y));

//     // from the final pixel positions, we sample from the original image
//     // transformation is:
//     // 1) pixel space -> sprite local space
//     // 2) rotate
//     // 3) scale
//     // 4) translate
//     // the inverse_transform does this in the inverse direction
//     const Mat3x3 translate_inv({
//         1, 0, -go->transform.pos.x,
//         0, 1, -go->transform.pos.y,
//         0, 0, 1
//     });
//     const Mat3x3 scale_inv(Vec3(-go->transform.scale.x, -go->transform.scale.y, 1));
//     const Mat3x3 rotate_inv = Mat3x3::rotation_matrix_z(-radians);
//     const Mat3x3 pixel2sprite_transform_inv = Mat3x3::translation_2d_matrix(&go->sprite.center);
//     const Mat3x3 inverse_transform =
//         translate_inv *
//         scale_inv *
//         rotate_inv *
//         pixel2sprite_transform_inv;

//     Vec3 pos(1,1,1);

//     for (int x = 0; x < x_diff; ++x) {
//         for (int y = 0; y < y_diff; ++y) {
//             // set pos to the global final position of the pixel
//             pos.x = x + go->transform.pos.x;
//             pos.y = y + go->transform.pos.y;

//             // inverse transform pos to pixel space
//             pos *= inverse_transform;

//             // sample the pixel in pixel space
//             const int px_space_r = static_cast<int>(pos.x);
//             const int px_space_c = static_cast<int>(pos.y);
//             // sanity check
//             if (px_space_r < 0 || px_space_r >= go->sprite.size.x) {
//                 throw std::runtime_error("Pixel sampling out of bounds (x)");
//             } else if (px_space_c < 0 || px_space_r>= go->sprite.size.y) {
//                 throw std::runtime_error("Pixel sampling out of bounds (y)");
//             }
//             color_precision_t *pixel = &go->sprite.pixels[px_space_r * go->sprite.size.x + px_space_c]; // this is a color_precision_t[4]
//         }
//     }
// }

// void Renderer2d::render(Renderer2d::buffer_t buffer, size_t width, size_t height) {

// }

// void Renderer2d::clear_buffer() {
//     clear_buffer(_buffer_2d[buffer_side], PHYBER_ENGINE_RENDERER_2D_RESOLUTION_WIDTH, PHYBER_ENGINE_RENDERER_2D_RESOLUTION_HEIGHT);
// }

// void Renderer2d::fill_buffer(color_precision_t r, color_precision_t g, color_precision_t b, color_precision_t a) {
//     fill_buffer(_buffer_2d[buffer_side], PHYBER_ENGINE_RENDERER_2D_RESOLUTION_WIDTH, PHYBER_ENGINE_RENDERER_2D_RESOLUTION_HEIGHT, r, g, b, a);
// }
