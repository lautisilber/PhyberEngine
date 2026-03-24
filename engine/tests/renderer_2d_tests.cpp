#include "phyber/event.h"
#include "phyber/2d/renderer.h"

int main() {
    Phyber::Renderer2D_cpu::init(500, 400);

    bool running = true;
    Phyber::Event event;
    while (running) {
        while (Phyber::poll_event(event)) {
            if (event.is_quit()) running = false;
        }


    }

    Phyber::Renderer2D_cpu::destroy();
}
