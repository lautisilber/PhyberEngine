#include "phyber/common_2d.h"
#include <stdlib.h>
#include <string.h>

using namespace Phyber;

void Sprite::reset() {
    if (pixels) {
        free(pixels);
    }
    size = Vec2Int(0,0);
    center = Vec2(0,0);
}

Sprite::~Sprite() {
    if (pixels) {
        free(pixels);
    }
}

void Transform2d::reset() {
    pos = Vec3(0,0,0);
    rot = 0;
    scale = Vec2(0,0);
}

void GameObject2d::reset() {
    transform.reset();
    sprite.reset();
}

Sprite phyber_create_sprite_from_pixels(Pixel2d pixels[], uint16_t x, uint16_t y) {
    const size_t n = x * y;
    const size_t size = sizeof(Pixel2d) * n;
    Pixel2d *new_pixels = (Pixel2d*)malloc(size);
    memcpy(new_pixels, pixels, size);
    Sprite sprite = {
        new_pixels,
        Vec2Int(x, y),
        Vec2(0, 0)
    };

    return sprite;
}

void phyber_delete_sprite(Sprite *sprite) {
    free(sprite->pixels);
};
