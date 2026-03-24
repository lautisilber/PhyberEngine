#include "phyber/2d/common.h"
#include <stdlib.h>
#include <string.h>

#include "stb/stb_image.h"

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

void Sprite::load_png(const char *fname) {
    const uint8_t forced_channels = 4;
    int width, height, channels;

    unsigned char* data = stbi_load(fname, &width, &height, &channels, forced_channels); // force RGBA
    if (!data) {
        throw std::runtime_error("Failed to load image");
    }

    std::vector<color_precision_t> pixels(width * height);

    for (int i = 0; i < width * height; ++i) {
        pixels.push_back(
            (data[i * forced_channels + 0] << 24) +
            (data[i * forced_channels + 1] << 16) +
            (data[i * forced_channels + 2] << 8) +
            (data[i * forced_channels + 3])
        );
    }

    load_pixels(pixels.data(), width, height);
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

void Transform2D::reset() {
    pos = glm::vec3(0,0,0);
    rot = 0;
    scale = glm::vec2(0,0);
}

void GameObject2D::reset() {
    transform.reset();
    sprite.reset();
}

void phyber_delete_sprite(Sprite *sprite) {
    free(sprite->pixels);
};
