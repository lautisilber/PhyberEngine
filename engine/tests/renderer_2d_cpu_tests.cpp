#include "phyber/renderer_2d.h"
#include "phyber/event.h"

using namespace Phyber;

int main() {
    Renderer2d_cpu::init(120, 90);

    Phyber::Event event;
    bool running = true;
    while (running) {
        while (Phyber::poll_event(event)) {
            if (event.type == Phyber::EventType::QUIT_EVENT) {
                running = false;
            }
        }
    }


    Renderer2d_cpu::deinit();
}
