#include "sdl_2D_cpu.h"

#include "phyber/logging.h"

#include <SDL3/SDL.h>
#include <stdlib.h>

size_t buffer_pitch = 0;
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Texture* texture = nullptr;
float dt_s = 1; // in s

void Phyber::Renderer2D_cpu::SDL::destroy() {

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Phyber::Renderer2D_cpu::SDL::init(color_precision_t *buffer, unsigned int width, unsigned int height) {
    // create a window
    window = SDL_CreateWindow("Hello, streaming texture!", width, height, 0);
    if (!window) {
        PHYBER_LOG_CRITICAL("Couldn't get window: %s", SDL_GetError());
        goto error;
    }

    // get renderer
    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        PHYBER_LOG_CRITICAL("Couldn't get renderer: %s", SDL_GetError());
        goto error;
    }

    // create texture
    texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        width,
        height
    );
    if (!texture) {
        PHYBER_LOG_CRITICAL("Couldn't create texture: %s", SDL_GetError());
        goto error;
    }

    return;

    error:
    Phyber::Renderer2D_cpu::SDL::destroy();
    exit(1);
}

bool Phyber::Renderer2D_cpu::SDL::draw(color_precision_t *buffer, unsigned int width, unsigned int height) {
    // update the texture
    size_t buffer_pitch = sizeof(color_precision_t) * width;
    if (!SDL_UpdateTexture(
        texture,                 // the texture to update.
        NULL,                    // an SDL_Rect structure representing the area to update, or NULL to update the entire texture.
        buffer,                  // the raw pixel data in the format of the texture.
        buffer_pitch // the number of bytes in a row of pixel data, including padding between lines.
    )) {
        PHYBER_LOG_ERROR("Couldn't update texture: ", SDL_GetError());
        return false;
    }

    // SDL_RenderClear(renderer);
    if (!SDL_RenderTexture(renderer, texture, NULL, NULL)) {
        PHYBER_LOG_ERROR("Couldn't render texture: ", SDL_GetError());
        return false;
    }
    if (!SDL_RenderPresent(renderer)) {
        PHYBER_LOG_ERROR("Couldn't present rendered texture: ", SDL_GetError());
        return false;
    }

    // update dt
    static uint64_t last_ticks = 0;
    uint64_t curr_ticks = SDL_GetTicks();
    dt_s = (curr_ticks - last_ticks) / 1000.0f;
    last_ticks = curr_ticks;

    return true;
}

float Phyber::Renderer2D_cpu::SDL::dt() {
    return dt_s;
}
