#ifndef BACKEND_SDL_EVENT_H
#define BACKEND_SDL_EVENT_H

#include "phyber/event.h"

namespace Phyber {
namespace EventBackend {
namespace SDL {

extern bool poll_event(Phyber::Event &event);
extern const char *get_key_name_from_virtual_key(const Phyber::KeyboardEvent::KeySymbol::VirtualKey &virtual_key);

}
}
}

#endif /* BACKEND_SDL_EVENT_H */
