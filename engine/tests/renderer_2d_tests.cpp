#include "phyber/event.h"
#include "phyber/renderer_2d.h"

int main() {
    Phyber::Renderer2d_cpu::init(500, 400);

    bool running = true;
    Phyber::Event event;
    while (running) {
        while (Phyber::poll_event(event)) {
            if (event.is_quit()) running = false;
        }


    }

    Phyber::Renderer2d_cpu::destroy();
}
