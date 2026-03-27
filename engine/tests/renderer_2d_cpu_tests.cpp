#include "phyber/logging.h"
#include "phyber/event.h"
#include "phyber/2d/renderer.h"
#include <cmath>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

Phyber::GameObject2D obj = {
    .transform = {
        .pos = glm::vec3(0),
        .rot = 0,
        .scale = glm::vec3(1)
    },
    .type = Phyber::GameObject2DType::GO2D_RECT,
    .rect = {
        .rect = {
            .top_left = glm::vec2(-.5, .5),
            .bottom_right = glm::vec2(.5, -.5)
        },
        .primitive = {
            .color = 0xF37024FF,
            .filled = false,
            .line_width = 1,
        }
    }
};

Phyber::Camera2D camera {
    .pos = glm::vec3(0, 0, -1),
    .rot = 0,
    .view_size = glm::vec2(2)
};

class AnimateValue {
private:
    float a;
    const float amin, amax;
    const bool bounce;
    float d;

public:
    AnimateValue(float init, float min, float max, float change, bool bounce) : a(init), amin(min), amax(max), d(abs(change)), bounce(bounce) {}
    float tick() {
        a += d;
        if (a >= amax) {
            if (bounce) {
                a = amax; d = -abs(d);
            } else {
                a = amin;
            }
        }
        else if (a <= amin) { a = amin; d = abs(d); }
        return a;
    }
};

#define TEST 2

int main() {
    #if TEST == 2
    Phyber::Renderer2D::add_go(obj);
    #endif

    unsigned int width = 500, height = 400;
    Phyber::Renderer2D::CPU::init(width, height, Phyber::Renderer2D::CPU::RasterizationQuality::ANTI_ALIASING);

    #if TEST == 0
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float r = (float)y / (height - 1);
            float b = (float)x / (width  - 1);
            Phyber::Renderer2D::CPU::pixel_buffer[y * width + x] =
                static_cast<uint8_t>(r * 255) << 24 |
                static_cast<uint8_t>(0 * 255) << 16 |
                static_cast<uint8_t>(b * 255) << 8 |
                static_cast<uint8_t>(1 * 255);
        }
    }
    #endif

    bool running = true;
    Phyber::Event event;
    while (running) {
        while (Phyber::poll_event(event)) {
            if (event.is_quit()) running = false;
        }

        #if TEST == 0

        Phyber::Renderer2D::CPU::draw();

        #elif TEST == 1

        static AnimateValue cycler(0, 0, 255, 1, true);
        color_precision_t c = 0x0000FFFF | (static_cast<color_precision_t>(cycler.tick()) << 16);
        Phyber::Renderer2D::CPU::fill(c);
        Phyber::Renderer2D::CPU::draw();

        #elif TEST == 2

        static AnimateValue r(0, 0, M_PI * 2, .01, false);
        obj.transform.rot = r.tick();

        Phyber::Renderer2D::CPU::fill(0x335F5BFF);
        Phyber::Renderer2D::CPU::render(camera);

        #endif


        float dt = Phyber::Renderer2D::CPU::dt();
        float fps = 1 / dt;
        PHYBER_LOG_DEBUG("fps: %f", fps);
    }

    Phyber::Renderer2D::CPU::destroy();
}
