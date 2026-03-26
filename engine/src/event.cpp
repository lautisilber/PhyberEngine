#include "phyber/event.h"
#include "phyber/logging.h"

#include "event_backends/sdl/sdl_event.h"

Phyber::poll_event_t Phyber::poll_event = Phyber::EventBackend::SDL::poll_event;
void Phyber::set_poll_event_func(poll_event_t poll_event_f) {
    Phyber::poll_event = poll_event_f;
}

const char *Phyber::KeyboardEvent::KeySymbol::get_key_name() const {
    return Phyber::EventBackend::SDL::get_key_name_from_virtual_key(virtual_key);
}

#define BUTTON_MASK(X)  (1u << ((X)-1))
#define BUTTON_LMASK    BUTTON_MASK(MouseButtonFlags::BUTTON_LEFT)
#define BUTTON_MMASK    BUTTON_MASK(MouseButtonFlags::BUTTON_MIDDLE)
#define BUTTON_RMASK    BUTTON_MASK(MouseButtonFlags::BUTTON_RIGHT)
#define BUTTON_X1MASK   BUTTON_MASK(MouseButtonFlags::BUTTON_X1)
#define BUTTON_X2MASK   BUTTON_MASK(MouseButtonFlags::BUTTON_X2)
bool Phyber::MouseMotionEvent::is_button_left() const {
    return BUTTON_LMASK & button_state;
}

bool Phyber::MouseMotionEvent::is_button_middle() const {
    return BUTTON_MMASK & button_state;
}

bool Phyber::MouseMotionEvent::is_button_right() const {
    return BUTTON_RMASK & button_state;
}

bool Phyber::MouseMotionEvent::is_button_x1() const {
    return BUTTON_X1MASK & button_state;
}

bool Phyber::MouseMotionEvent::is_button_x2() const {
    return BUTTON_X2MASK & button_state;
}
