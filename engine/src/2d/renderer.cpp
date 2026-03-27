#include "phyber/2d/renderer.h"
#include "phyber/2d/common.h"
#include "phyber/logging.h"

#include <exception>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective

#include <cmath>
#include <limits>
#include <stdexcept>
#include <memory.h>
#include <string.h>
#include <utility>
#include <vector>
#include <algorithm>

#include "backends/sdl/sdl_2D_cpu.h"

color_precision_t *Phyber::Renderer2D::CPU::pixel_buffer = nullptr;
z_buffer_precision_t *Phyber::Renderer2D::CPU::z_buffer = nullptr;
unsigned int g_width = 0, g_height = 0;
Phyber::Renderer2D::CPU::RasterizationQuality g_rasterization_quality = Phyber::Renderer2D::CPU::RasterizationQuality::SUBPIXEL_PRECISION;

Phyber::Renderer2D::init_backend_t b_init = nullptr;
Phyber::Renderer2D::draw_backend_t b_draw = nullptr;
Phyber::Renderer2D::dt_backend_t b_dt = nullptr;
Phyber::Renderer2D::destroy_backend_t b_destroy = nullptr;

std::vector<Phyber::GameObject2D*> gos;

// render-specific functions

static void local_to_world(const glm::vec2 &local_pos, glm::vec3 &world_pos, const Phyber::Transform2D &transform) {
    /*
     * 1. Scale
     * 2. Rotate
     * 3. Translate
     */

    const float c = cosf(transform.rot);
    const float s = sinf(transform.rot);
    const glm::mat2x2 scale_mat(
        transform.scale.x, 0,
        0, transform.scale.y
    );
    const glm::mat2x2 rotate_mat(
        c, -s,
        s, c
    );

    const glm::vec2 temp = rotate_mat * scale_mat * local_pos;
    world_pos = glm::vec3(temp.x + transform.pos.x, temp.y + transform.pos.y, transform.pos.y);
}

static bool world_to_camera(const glm::vec3 &world_pos, glm::vec2 & camera_pos, const Phyber::Camera2D &camera) {
    // returns true if in camera, false if outside camera
    /*
     * 1. Transform world to camera
     * 2. Rotate
     * 3. Scale
     */

    const float c = cosf(-camera.rot);
    const float s = sinf(-camera.rot);
    const glm::mat2x2 antirot(
        c, -s,
        s, c
    );
    const glm::mat2x2 antiscale(
        1/camera.view_size.x, 0,
        0, 1/camera.view_size.y
    );

    const glm::vec2 world_pos_2d(world_pos.x, world_pos.y);
    camera_pos = antiscale * antirot * (world_pos_2d - glm::vec2(camera.pos.x, camera.pos.y));
    return abs(camera_pos.x) > 1 || abs(camera_pos.y) > 1 || world_pos.z > camera.pos.z;
}

static bool camera_to_buffer(const glm::vec2 &camera_pos, glm::vec2 &buffer_pos, unsigned int w=g_width, unsigned int h=g_height) {
    buffer_pos.x = (camera_pos.x + 1) * w * 0.5;
    buffer_pos.y = (camera_pos.y + 1) * h * 0.5;
    return (buffer_pos.x < 0 || buffer_pos.x >= w || buffer_pos.y < 0 || buffer_pos.y >= h);
}

static bool local_to_buffer(const glm::vec3 &local_pos, glm::vec2 &buffer_pos, const Phyber::Transform2D &transform, const Phyber::Camera2D &camera, unsigned int w=g_width, unsigned int h=g_height) {
    glm::vec3 world_pos;
    glm::vec2 camera_pos;

    local_to_world(local_pos, world_pos, transform);
    world_to_camera(world_pos, camera_pos, camera);
    return camera_to_buffer(camera_pos, buffer_pos, w, h);
}

static void raster_line_to_buffer(const glm::ivec2 &a, const glm::ivec2 &b, z_buffer_precision_t z, color_precision_t color, unsigned int linewidth) {
    // https://en.wikipedia.org/wiki/Line_drawing_algorithm
    if (linewidth == 0) {
        PHYBER_LOG_DEBUG("Trying to raster line with linewidth = 0");
        return;
    }

    float x0 = a.x, x1 = b.x, y0 = a.y, y1 = b.y;
    const bool steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) {
        std::swap(x0, y0);
        std::swap(x1, y1);
    }
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    const float dx = x1 - x0;
    const float dy = y1 - y0;

    switch (g_rasterization_quality) {
    case Phyber::Renderer2D::CPU::RasterizationQuality::SUBPIXEL_PRECISION: {
        const float m = dy / dx;
        if (linewidth == 1) {
            size_t buffer_idx;
            for (float x = x0; x <= x1; ++x) {
                float y = m * (x - x0) + y0;
                const int ix = roundf(x);
                const int iy = roundf(y);

                if (steep) {
                    // check if pixel outside buffer
                    if (iy < 0 || ix >= g_width || ix < 0 || iy >= g_height) { continue; }
                    // check for zbuffer
                    buffer_idx = iy + g_width * ix;
                } else {
                    // check if pixel outside buffer
                    if (ix < 0 || ix >= g_width || iy < 0 || iy >= g_height) { continue; }
                    // check for zbuffer
                    buffer_idx = ix + g_width * iy;
                }
                if (Phyber::Renderer2D::CPU::z_buffer[buffer_idx] > z) { continue; }
                Phyber::Renderer2D::CPU::pixel_buffer[buffer_idx] = color;
            }
        } else {
            size_t buffer_idx;
            for (float x = x0; x <= x1; ++x) {
                float y = m * (x - x0) + y0;
                const int ix = roundf(x);
                const int iy = roundf(y);

                if (steep) {
                    // check if pixel outside buffer
                    if (iy < 0 || ix >= g_width || ix < 0 || iy >= g_height) { continue; }
                    // check for zbuffer
                    buffer_idx = iy + g_width * ix;
                } else {
                    // check if pixel outside buffer
                    if (ix < 0 || ix >= g_width || iy < 0 || iy >= g_height) { continue; }
                    // check for zbuffer
                    buffer_idx = ix + g_width * iy;
                }
                if (Phyber::Renderer2D::CPU::z_buffer[buffer_idx] > z) { continue; }
                Phyber::Renderer2D::CPU::pixel_buffer[buffer_idx] = color;
            }
        }
        break;
    }
    case Phyber::Renderer2D::CPU::RasterizationQuality::ANTI_ALIASING: {
        // https://en.wikipedia.org/wiki/Xiaolin_Wu%27s_line_algorithm#Floating_Point_Implementation
        auto plot = [&](int x, int y, float brightness, z_buffer_precision_t z, color_precision_t c) {
            // plot the pixel at (x, y) with brightness c (where 0 <= c <= 1)
            if (x < 0 || x >= g_width || y < 0 || y >= g_height) { return; }
            const size_t buffer_idx = x + g_width * y;
            if (Phyber::Renderer2D::CPU::z_buffer[buffer_idx] > z) { return; }

            // map brightness [0-1] to curr max brightness
            const color_precision_t new_brightness = static_cast<float>(c & COLOR_MASK_ALPHA) * brightness;
            const color_precision_t new_color = c & (~COLOR_MASK_ALPHA) + new_brightness;
            Phyber::Renderer2D::CPU::pixel_buffer[buffer_idx] = new_color;
        };

        // fractional part of x
        auto fpart = [](float x) -> float {
            return x - floorf(x);
        };

        auto rfpart = [&fpart](float x) -> float {
            return 1 - fpart(x);
        };

        const float gradient = (dx == 0 ? 1.0 : dy/dx);

        // handle first endpoint
        float xend = floorf(x0);
        float yend = y0 + gradient * (xend - x0);
        float xgap = 1 - (x0 - xend);
        int xpxl1 = xend; // this will be used in the main loop
        int ypxl1 = floorf(yend);
        if (steep) {
            plot(ypxl1,   xpxl1, rfpart(yend) * xgap, z, color);
            plot(ypxl1+1, xpxl1,  fpart(yend) * xgap, z, color);
        } else {
            plot(static_cast<int>(ypxl1), static_cast<int>(xpxl1),   rfpart(yend) * xgap, z, color);
            plot(static_cast<int>(ypxl1), static_cast<int>(xpxl1+1),  fpart(yend) * xgap, z, color);
        }
        float intery = yend + gradient; // first y-intersection for the main loop

        // handle second endpoint
        xend = ceilf(x1);
        yend = y1 + gradient * (xend - x1);
        xgap = 1 - (xend - x1);
        float xpxl2 = xend; //this will be used in the main loop
        float ypxl2 = floorf(yend);
        if (steep) {
            plot(static_cast<int>(ypxl2)  , static_cast<int>(xpxl2), rfpart(yend) * xgap, z, color);
            plot(static_cast<int>(ypxl2+1), static_cast<int>(xpxl2),  fpart(yend) * xgap, z, color);
        } else {
            plot(static_cast<int>(ypxl2), static_cast<int>(xpxl2),  rfpart(yend) * xgap, z, color);
            plot(static_cast<int>(ypxl2), static_cast<int>(xpxl2+1), fpart(yend) * xgap, z, color);
        }
        if (steep) {
            for (int x = xpxl1 + 1; x <= xpxl2 - 1; ++x) {
                plot(floorf(intery)  , x, rfpart(intery), z, color);
                plot(floorf(intery)+1, x,  fpart(intery), z, color);
                intery += gradient;
            }
        } else {
            for (int x = xpxl1 + 1; x <= xpxl2 - 1; ++x) {
                plot(floorf(intery)+1, x, rfpart(intery), z, color);
                plot(floorf(intery)  , x,  fpart(intery), z, color);
                intery += gradient;
            }
        }
        break;
    }
    default:
        PHYBER_LOG_CRITICAL("Unreachable (%u)", g_rasterization_quality);
        abort();
    }
}

static void raster_rect_to_buffer(const glm::vec2 &top_left, const glm::vec2 &top_right, const glm::vec2 &bottom_right, const glm::vec2 &bottom_left, z_buffer_precision_t z, color_precision_t color, bool filled, float line_width) {
    const glm::ivec2 i_top_left = top_left;
    const glm::ivec2 i_top_right = top_right;
    const glm::ivec2 i_bottom_right = bottom_right;
    const glm::ivec2 i_bottom_left = bottom_left;
    PHYBER_LOG_DEBUG("local: (%f, %f), (%f, %f)", top_left.x, top_left.y, bottom_right.x, bottom_right.y);
    raster_line_to_buffer(i_top_left, i_top_right, z, color, line_width);
    raster_line_to_buffer(i_top_right, i_bottom_right, z, color, line_width);
    raster_line_to_buffer(i_bottom_right, i_bottom_left, z, color, line_width);
    raster_line_to_buffer(i_bottom_left, i_top_left, z, color, line_width);
}

static void raster_go2D(const Phyber::GameObject2D &go, const Phyber::Camera2D &camera) {
    switch (go.type) {
    case Phyber::GameObject2DType::GO2D_RECT: {
        const glm::vec3 top_left_local = glm::vec3(go.rect.rect.top_left.x, go.rect.rect.top_left.y, 0);
        const glm::vec3 bottom_right_local = glm::vec3(go.rect.rect.bottom_right.x, go.rect.rect.bottom_right.y, 0);
        const glm::vec3 top_right_local = glm::vec3(bottom_right_local.x, top_left_local.y, 0);
        const glm::vec3 bottom_left_local = glm::vec3(top_left_local.x, bottom_right_local.y, 0);
        glm::vec2 top_left_buffer, bottom_right_buffer, top_right_buffer, bottom_left_buffer;
        local_to_buffer(top_left_local, top_left_buffer, go.transform, camera, g_width, g_height);
        local_to_buffer(top_right_local, top_right_buffer, go.transform, camera, g_width, g_height);
        local_to_buffer(bottom_right_local, bottom_right_buffer, go.transform, camera, g_width, g_height);
        local_to_buffer(bottom_left_local, bottom_left_buffer, go.transform, camera, g_width, g_height);

        raster_rect_to_buffer(top_left_buffer, top_right_buffer, bottom_right_buffer, bottom_left_buffer, go.transform.pos.z, go.rect.primitive.color, go.rect.primitive.filled, go.rect.primitive.line_width);
        break;
    }
    default:
        PHYBER_LOG_DEBUG("Not implemented");
        abort();
    }
}

// exposed functions

void Phyber::Renderer2D::CPU::init(unsigned int width, unsigned int height, RasterizationQuality rasterization_quality, init_backend_t init_f, draw_backend_t draw_f, dt_backend_t dt_f, destroy_backend_t destroy_f) {
    const bool no_overrides = init_f == nullptr || draw_f == nullptr || dt_f == nullptr || destroy_f == nullptr;
    const bool all_overrides = init_f != nullptr && draw_f != nullptr && dt_f != nullptr && destroy_f != nullptr;

    if (no_overrides) {
        b_init = Phyber::Renderer2D::CPU::SDL::init;
        b_draw = Phyber::Renderer2D::CPU::SDL::draw;
        b_dt = Phyber::Renderer2D::CPU::SDL::dt;
        b_destroy = Phyber::Renderer2D::CPU::SDL::destroy;
    } else if (all_overrides) {
        b_init = init_f;
        b_draw = draw_f;
        b_dt = dt_f;
        b_destroy = destroy_f;
    } else {
        throw std::runtime_error("If one backend function wasn't provided, then no backend function should be provided");
    }

    g_rasterization_quality = rasterization_quality;

    g_width = width;
    g_height = height;
    size_t buffer_pitch = sizeof(color_precision_t) * g_width;
    Phyber::Renderer2D::CPU::pixel_buffer = (color_precision_t*)malloc(buffer_pitch * g_height);
    if (!Phyber::Renderer2D::CPU::pixel_buffer) {
        PHYBER_LOG_CRITICAL("Coudln't allocate pixel buffer");
        destroy();
        exit(1);
    }

    Phyber::Renderer2D::CPU::z_buffer = (z_buffer_precision_t*)malloc(g_width * g_height * sizeof(z_buffer_precision_t));
    if (!Phyber::Renderer2D::CPU::z_buffer) {
        PHYBER_LOG_CRITICAL("Coudln't allocate z buffer");
        destroy();
        exit(1);
    }

    fill(0);

    b_init(Phyber::Renderer2D::CPU::pixel_buffer, g_width, g_height);
}

bool Phyber::Renderer2D::CPU::render(const Phyber::Camera2D &camera) {
    for (const Phyber::GameObject2D *go : gos) {
        raster_go2D(*go, camera);
    }

    return draw();
}

bool Phyber::Renderer2D::CPU::draw() {
    return b_draw(Phyber::Renderer2D::CPU::pixel_buffer, g_width, g_height);
}

float Phyber::Renderer2D::CPU::dt() {
    return b_dt();
}

void Phyber::Renderer2D::CPU::destroy() {
    if (Phyber::Renderer2D::CPU::pixel_buffer) { free(Phyber::Renderer2D::CPU::pixel_buffer); }
        if (Phyber::Renderer2D::CPU::z_buffer) { free(Phyber::Renderer2D::CPU::z_buffer); }

    b_destroy();
}

bool Phyber::Renderer2D::add_go(GameObject2D &go) {
    if (std::find(gos.begin(), gos.end(), &go) != gos.end()) { return false; }
    gos.push_back(&go);
    return true;
}

bool Phyber::Renderer2D::remove_go(GameObject2D &go) {
    auto ptr = std::find(gos.begin(), gos.end(), &go);
    if (ptr == gos.end()) { return false; }
    gos.erase(ptr);
    return true;
}

extern void Phyber::Renderer2D::CPU::fill(color_precision_t color) {
    std::fill(Phyber::Renderer2D::CPU::pixel_buffer, Phyber::Renderer2D::CPU::pixel_buffer + g_width * g_height, color);
    std::fill(Phyber::Renderer2D::CPU::z_buffer, Phyber::Renderer2D::CPU::z_buffer + g_width * g_height, std::numeric_limits<z_buffer_precision_t>::min());
}

void abort() {
    Phyber::Renderer2D::CPU::destroy();
    exit(1);
}
