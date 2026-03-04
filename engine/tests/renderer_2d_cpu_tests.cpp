#include "phyber/renderer_2d.h"
#include "phyber/event.h"
#include "phyber/logging.h"

using namespace Phyber;

int main() {
    Renderer2d_cpu::init(500, 400);

    Phyber::Event event;
    bool running = true;
    while (running) {
        while (Phyber::poll_event(event)) {
            if (event.type == Phyber::EventType::QUIT_EVENT) {
                PHYBER_LOG_DEBUG("Event: Quit");
                running = false;
            } else if (event.type == Phyber::EventType::KEYBOARD) {
                PHYBER_LOG_DEBUG("Event: Keyboard");
            } else if (event.type == Phyber::EventType::MOUSE_MOTION) {
                PHYBER_LOG_DEBUG("Event: Mouse (%f, %f)", event.mouse_motion.x, event.mouse_motion.y);
            }
        }
    }


    Renderer2d_cpu::deinit();
}
