#ifndef PHYBER_ENGINE_COMMON_2D_H
#define PHYBER_ENGINE_COMMON_2D_H

#include <stddef.h>
#include <stdint.h>

#include "phyber/math.h"

namespace Phyber {

typedef struct {
    uint8_t r, g, b, a;
} Phyber2DPixel;

typedef struct {
    Phyber2DPixel *pixels;
    uint16_t width, height;
    float center_x, center_y;
} PhyberSprite;

typedef struct {
    PhyberVec3 pos; // cartesian
    float rot; // rotation in z axis
    PhyberVec2 scale;
} PhyberTransform2d;

typedef struct {
    PhyberTransform2d transform;
    PhyberSprite sprite;
} Phyber2DGameObject;

typedef struct {
    float top, left, bottom, right;
} PhyberCollider2DSquare;

// typedef struct {
//     float radius;
// } PhyberCollider2DCirlce;

// TODO: figure out how to have multiple collider types
typedef struct {
    Phyber2DGameObject go;
    PhyberCollider2DSquare collider;
    float collider_plasticity;
} PhyberRigidBodyStatic2D;

typedef struct {
    PhyberRigidBodyStatic2D static_rbody;
    float vel_x, vel_y, vel_z;
    float mass;
} PhyberRigidBodyDynamic2D;

extern PhyberSprite phyber_create_sprite_from_pixels(Phyber2DPixel pixels[], uint16_t x, uint16_t y);
extern void phyber_delete_sprite(PhyberSprite *pixel);

}

#endif /* PHYBER_ENGINE_COMMON_2D_H */
