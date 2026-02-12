#ifndef PHYBER_ENGINE_RENDERER_2D_H
#define PHYBER_ENGINE_RENDERER_2D_H

#include "common_2d.h"

#ifndef PHYBER_ENGINE_RENDERER_2D_MAX_GAME_OBJECTS
#define PHYBER_ENGINE_RENDERER_2D_MAX_GAME_OBJECTS 256
#endif

#if !defined(PHYBER_ENGINE_RESOLUTION_PX_WIDTH) || !defined(PHYBER_ENGINE_RESOLUTION_PX_HEIGHT)
#define PHYBER_ENGINE_RESOLUTION_PX_WIDTH 256
#define PHYBER_ENGINE_RESOLUTION_PX_HEIGHT 256
#endif

extern bool phyber_add_game_object_to_stack(const Phyber2DGameObject *go);
extern bool phyber_remove_game_object_to_stack(const Phyber2DGameObject *go);

extern void phyber_render_2d();

#endif /* PHYBER_ENGINE_RENDERER_2D_H */
