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

struct Texture {
    Texture() {}
    ~Texture();

    color_precision_t *pixels = nullptr; // r, g, b, a
    glm::uvec2 size_uv;
    bool transparent; // oposed to opaque

    void load_png(const char *fname);
    void load_pixels(color_precision_t *pixels, size_t width, size_t height);
    void reset();
};

struct Sprite {
    Texture *texture = nullptr;
    glm::vec2 center_uv;

    void reset();
};

struct Rect {
    glm::vec2 top_left, bottom_right;
};

struct Oval {
    float radius_h, radius_v;
};

struct Primitive {
    color_precision_t color;
    bool filled;
    float line_width;
};

struct RectPrimitive {
    Rect rect;
    Primitive primitive;
};

struct OvalPrimitive {
    Oval oval;
    Primitive primitive;
};

enum GameObject2DType {
    GO2D_RECT, GO2D_OVAL, GO2D_SPRITE
};

struct Transform2D {
    glm::vec3 pos; // cartesian
    float rot; // rotation in z axis
    glm::vec2 scale;

    void reset();
};

struct GameObject2D {
    Transform2D transform;

    GameObject2DType type;
    union {
        RectPrimitive rect;
        OvalPrimitive oval;
        Sprite sprite;
    };

    void reset();
};

enum Collider2DShapeType {
    CO2D_RECT, CO2D_OVAL
};

struct Collider2DRect: Rect {
};

struct Collider2DOval: Oval {
};

struct Collider2D {
    Collider2DShapeType shape_type;
    union {
        Collider2DRect rect;
        Collider2DOval oval;
    };
};

struct PhyberRigidBodyStatic2D {
    GameObject2D go;

    Collider2D collider;
    float collider_plasticity;
};

struct PhyberRigidBodyDynamic2D {
    PhyberRigidBodyStatic2D static_rbody;
    glm::vec3 vel;
    float mass;
};

struct Camera2D {
    glm::vec3 pos;
    float rot; // rotation in z axis
    glm::vec2 view_size;
};

}

#endif /* PHYBER_ENGINE_COMMON_2D_H */
