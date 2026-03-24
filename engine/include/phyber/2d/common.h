#ifndef PHYBER_ENGINE_COMMON_2D_H
#define PHYBER_ENGINE_COMMON_2D_H

#include <cstdint>
#include <stddef.h>
#include <stdint.h>

#include "phyber/defs/global_defines.h"
#include "phyber/defs/global_defines.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace Phyber {

struct Sprite {
    color_precision_t *pixels = nullptr; // r, g, b, a
    glm::uvec2 size_uv;
    glm::uvec2 center_uv;
    bool transparent; // oposed to opaque

    Sprite() {}
    Sprite(color_precision_t *pixels, size_t width, size_t height, int center_x, int center_y);
    ~Sprite();

    void load_pixels(color_precision_t *pixels, size_t width, size_t height);
    void reset();
};

struct Transform2d {
    glm::vec3 pos; // cartesian
    float rot; // rotation in z axis
    glm::vec2 scale;

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
    glm::vec3 vel;
    float mass;
};

}

#endif /* PHYBER_ENGINE_COMMON_2D_H */
