#include "phyber/common_2d.h"
#include <stdlib.h>
#include <string.h>

using namespace Phyber;

PhyberSprite phyber_create_sprite_from_pixels(Phyber2DPixel pixels[], uint16_t x, uint16_t y) {
    const size_t n = x * y;
    const size_t size = sizeof(Phyber2DPixel) * n;
    Phyber2DPixel *new_pixels = (Phyber2DPixel*)malloc(size);
    memcpy(new_pixels, pixels, size);
    PhyberSprite sprite = {
        new_pixels,
        x, y,
        0, 0
    };

    return sprite;
}

void phyber_delete_sprite(PhyberSprite *sprite) {
    free(sprite->pixels);
};
