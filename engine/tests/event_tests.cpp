#include "phyber/2d/renderer.h"
#include "phyber/event.h"
#include "phyber/logging.h"

#include <chrono>

using namespace Phyber;

class Timer {
private:
    using clock_t    = std::chrono::steady_clock;
    using duration_t = std::chrono::milliseconds;

    std::chrono::time_point<clock_t> start_time;
    duration_t dt;

    static inline std::chrono::time_point<clock_t> now() {
        return clock_t::now();
    }

    inline duration_t elapsed() const {
        return std::chrono::duration_cast<duration_t>(
            now() - start_time
        );
    }

    inline void set_start_time() {
        start_time = now();
    }

public:
    Timer(unsigned int delay_ms) : Timer(duration_t(delay_ms)) {}
    Timer(duration_t delay) : dt(delay) {
        set_start_time();
        start_time -= dt;
    }

    bool has_elapsed() {
        if (elapsed() >= dt) {
            set_start_time(); // auto-reset
            return true;
        }
        return false;
    }
};

bool mouse_motion_timer() {
    static Timer t(1000);
    return t.has_elapsed();
}

int main() {
    Renderer2d_cpu::init(500, 400);

    Phyber::Event event;
    bool running = true;
    while (running) {
        while (Phyber::poll_event(event)) {
            if (event.is_quit()) {
                PHYBER_LOG_INFO("Event: Quit");
                running = false;
            } else if (event.type == Phyber::EventType::KEYBOARD) {
                PHYBER_LOG_INFO("Event: Keyboard %s - down: %u, repeat: %u",
                    event.keyboard.key.get_key_name(),
                    event.keyboard.down,
                    event.keyboard.repeat
                );
            } else if (event.type == Phyber::EventType::MOUSE_MOTION) {
                static size_t n_buffered_mouse_motion_events = 0;
                if (mouse_motion_timer()) {
                    PHYBER_LOG_INFO("Event: Mouse motion (%f, %f) %u%u%u%u%u | %lu buffered",
                        event.mouse_motion.x,
                        event.mouse_motion.y,
                        event.mouse_motion.is_button_left(),
                        event.mouse_motion.is_button_middle(),
                        event.mouse_motion.is_button_right(),
                        event.mouse_motion.is_button_x1(),
                        event.mouse_motion.is_button_x2(),
                        n_buffered_mouse_motion_events+1
                    );
                    n_buffered_mouse_motion_events = 0;
                } else {
                    ++n_buffered_mouse_motion_events;
                }
            } else if (event.type == Phyber::EventType::MOUSE_BUTTON) {
                PHYBER_LOG_INFO("Event: Mouse button (%f, %f) %u%u%u%u%u - down: %u, n_clicks: %u",
                    event.mouse_button.x,
                    event.mouse_button.y,
                    event.mouse_button.button == Phyber::MouseButtonFlags::BUTTON_LEFT,
                    event.mouse_button.button == Phyber::MouseButtonFlags::BUTTON_MIDDLE,
                    event.mouse_button.button == Phyber::MouseButtonFlags::BUTTON_RIGHT,
                    event.mouse_button.button == Phyber::MouseButtonFlags::BUTTON_X1,
                    event.mouse_button.button == Phyber::MouseButtonFlags::BUTTON_X2,
                    event.mouse_button.down,
                    event.mouse_button.clicks
                );
            } else if (event.type == Phyber::EventType::MOUSE_WHEEL) {
                PHYBER_LOG_INFO("Event: Mouse wheel: scroll (%.2f, %.2f), direction %i, mouse coord (%f, %f), ticks (%i, %i)",
                    event.mouse_wheel.x,
                    event.mouse_wheel.y,
                    event.mouse_wheel.direction == Phyber::MouseWheelEvent::Direction::FLIPPED,
                    event.mouse_wheel.mouse_x,
                    event.mouse_wheel.mouse_y,
                    event.mouse_wheel.integer_x,
                    event.mouse_wheel.integer_y
                );
            }
        }
    }


    Renderer2d_cpu::destroy();
}
