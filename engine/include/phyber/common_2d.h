#ifndef PHYBER_ENGINE_COMMON_2D_H
#define PHYBER_ENGINE_COMMON_2D_H

#include <cstdint>
#include <stddef.h>
#include <stdint.h>

#include "math.h"
#include "phyber/math.h"

namespace Phyber {

typedef struct {
    uint8_t r, g, b, a;
} Pixel2d;

typedef struct {
    Pixel2d *pixels;
    Vec2Int size;
    Vec2 center;
} Sprite;

typedef struct {
    Vec3 pos; // cartesian
    float rot; // rotation in z axis
    Vec2 scale;
} Transform2d;

typedef struct {
    Transform2d transform;
    Sprite sprite;
} GameObject2d;

typedef struct {
    float top, left, bottom, right;
} Collider2dSquare;

// typedef struct {
//     float radius;
// } PhyberCollider2DCirlce;

// TODO: figure out how to have multiple collider types
typedef struct {
    GameObject2d go;
    Collider2dSquare collider;
    float collider_plasticity;
} PhyberRigidBodyStatic2D;

typedef struct {
    PhyberRigidBodyStatic2D static_rbody;
    float vel_x, vel_y, vel_z;
    float mass;
} PhyberRigidBodyDynamic2D;

extern Sprite phyber_create_sprite_from_pixels(Pixel2d pixels[], uint16_t x, uint16_t y);
extern void phyber_delete_sprite(Sprite *pixel);

}

#endif /* PHYBER_ENGINE_COMMON_2D_H */
