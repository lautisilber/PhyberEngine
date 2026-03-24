#include "phyber/2d/common.h"
#include <stdlib.h>
#include <string.h>

using namespace Phyber;

bool pixels_are_opaque(color_precision_t *pixels, size_t width, size_t height) {
    for (size_t i = 0; i < width * height; ++i) {
        if ((pixels[i] & COLOR_MASK_ALPHA) != 0x000000FF) { return false; }
    }
    return true;
}

Sprite::Sprite(color_precision_t *pixels, size_t width, size_t height, int center_x, int center_y) {
    transparent = pixels_are_opaque(pixels, width, height);
}

void Sprite::load_pixels(color_precision_t *pixels, size_t width, size_t height) {
    if (pixels) {
        free(pixels);
    }
    pixels = (color_precision_t *)malloc(width * height * 4 * sizeof(color_precision_t));
    transparent = pixels_are_opaque(pixels, width, height);
    size_uv = glm::uvec2(width, height);
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
    size_uv = glm::uvec2(0, 0);
    center_uv = glm::uvec2(0, 0);
    transparent = false;
}

void Transform2d::reset() {
    pos = glm::vec3(0,0,0);
    rot = 0;
    scale = glm::vec2(0,0);
}

void GameObject2d::reset() {
    transform.reset();
    sprite.reset();
}

void phyber_delete_sprite(Sprite *sprite) {
    free(sprite->pixels);
};
