#include "phyber/common_2d.h"
#include <stdlib.h>
#include <string.h>

using namespace Phyber;

Sprite::Sprite(color_precision_t *pixels, size_t width, size_t height, int center_x, int center_y) {

}

void Sprite::load_pixels(color_precision_t *pixels, size_t width, size_t height) {
    if (pixels) {
        free(pixels);
    }
    pixels = (color_precision_t *)malloc(width * height * 4 * sizeof(color_precision_t));
    size = Phyber::Vec2Int(width, height);
}


Sprite::~Sprite() {
    if (pixels) {
        free(pixels);
    }
}

void Sprite::reset() {
    if (pixels) {
        free(pixels);
    }
    size = Vec2Int(0,0);
    center = Vec2(0,0);
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

void phyber_delete_sprite(Sprite *sprite) {
    free(sprite->pixels);
};
