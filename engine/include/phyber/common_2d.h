#ifndef PHYBER_ENGINE_COMMON_2D_H
#define PHYBER_ENGINE_COMMON_2D_H

#include <cstdint>
#include <stddef.h>
#include <stdint.h>

#include "phyber/math.h"
#include "phyber/defs/global_defines.h"

namespace Phyber {

struct Pixel2d {
    color_precision_t r, g, b, a;
};

struct Sprite {
    Pixel2d *pixels;
    Vec2Int size;
    Vec2 center;

    void reset();
    ~Sprite();
};

struct Transform2d {
    Vec3 pos; // cartesian
    float rot; // rotation in z axis
    Vec2 scale;

    void reset();
};

struct GameObject2d {
    Transform2d transform;
    Sprite sprite;

    void reset();
};

struct Collider2dSquare {
    float top, left, bottom, right;
};

// typedef struct {
//     float radius;
// } PhyberCollider2DCirlce;

// TODO: figure out how to have multiple collider types
struct PhyberRigidBodyStatic2D {
    GameObject2d go;
    Collider2dSquare collider;
    float collider_plasticity;
};

struct PhyberRigidBodyDynamic2D {
    PhyberRigidBodyStatic2D static_rbody;
    float vel_x, vel_y, vel_z;
    float mass;
};

extern Sprite phyber_create_sprite_from_pixels(Pixel2d pixels[], uint16_t x, uint16_t y);
extern void phyber_delete_sprite(Sprite *pixel);

}

#endif /* PHYBER_ENGINE_COMMON_2D_H */
