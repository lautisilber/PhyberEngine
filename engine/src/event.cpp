#include "phyber/event.h"
#include <SDL3/SDL.h>

bool Phyber::poll_event(Phyber::Event &event) {
    SDL_Event sdl_event;
    if (!SDL_PollEvent(&sdl_event)) {
        return false;
    }

    // sdl_event.
    switch (sdl_event.type) {
    case SDL_EventType::SDL_EVENT_QUIT:
        event.type = Phyber::EventType::QUIT_EVENT;
        break;
    case SDL_EventType::SDL_EVENT_KEY_DOWN:
    case SDL_EventType::SDL_EVENT_KEY_UP:
        event.type = Phyber::EventType::KEYBOARD;
        event.keyboard.down = sdl_event.key.down;
        event.keyboard.repeat = sdl_event.key.repeat;
        event.keyboard.key.physical_key = static_cast<Phyber::KeyboardEvent::KeySymbol::PhysicalKey>(sdl_event.key.scancode);
        event.keyboard.key.virtual_key = static_cast<Phyber::KeyboardEvent::KeySymbol::VirtualKey>(sdl_event.key.key);
        event.keyboard.key.key_modifier = static_cast<Phyber::KeyboardEvent::KeySymbol::KeyModifier>(sdl_event.key.mod);
        break;
    case SDL_EventType::SDL_EVENT_MOUSE_MOTION:
        event.type = Phyber::EventType::MOUSE_MOTION;
        event.mouse_motion.button_state = sdl_event.motion.state;
        event.mouse_motion.x = sdl_event.motion.x;
        event.mouse_motion.y = sdl_event.motion.y;
        event.mouse_motion.dx = sdl_event.motion.xrel;
        event.mouse_motion.dy = sdl_event.motion.yrel;
        break;
    case SDL_EventType::SDL_EVENT_MOUSE_BUTTON_DOWN:
    case SDL_EventType::SDL_EVENT_MOUSE_BUTTON_UP:
        event.type = Phyber::EventType::MOUSE_BUTTON;
        event.mouse_button.button = sdl_event.button.button;
        event.mouse_button.down = sdl_event.button.down;
        event.mouse_button.clicks = sdl_event.button.clicks;
        event.mouse_button.x = sdl_event.button.x;
        event.mouse_button.y = sdl_event.button.y;
        break;
    case SDL_EventType::SDL_EVENT_MOUSE_WHEEL:
        event.type = Phyber::EventType::MOUSE_WHEEL;
        event.mouse_wheel.x = sdl_event.wheel.x;
        event.mouse_wheel.y = sdl_event.wheel.y;
        event.mouse_wheel.direction = static_cast<Phyber::MouseWheelEvent::Direction>(sdl_event.wheel.direction);
        event.mouse_wheel.mouse_x = sdl_event.wheel.mouse_x;
        event.mouse_wheel.mouse_y = sdl_event.wheel.mouse_y;
        event.mouse_wheel.integer_x = sdl_event.wheel.integer_x;
        event.mouse_wheel.integer_y = sdl_event.wheel.integer_y;
        break;
    default:
        break;
    };

    return true;
}
