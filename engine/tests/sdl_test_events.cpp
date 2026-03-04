#include <SDL3/SDL.h>
#include <stdexcept>
#include <string.h>

#define WIDTH 960
#define HEIGHT 540

// SDL_PIXELFORMAT_RGBA8888
uint32_t pixels[HEIGHT * WIDTH * 4];

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* texture;

#define MOUSE_BUTTON_NAME_BUF_LEN 32

void populate_pixels() {
    // RGBA format
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            float r = (float)y / (HEIGHT - 1);
            float b = (float)x / (WIDTH  - 1);
            pixels[y * WIDTH + x] =
                static_cast<uint8_t>(r * 255) << 24 |
                static_cast<uint8_t>(0 * 255) << 16 |
                static_cast<uint8_t>(b * 255) << 8 |
                static_cast<uint8_t>(1 * 255);
        }
    }
}

void get_mouse_button_name(SDL_Event &event, char buffer[MOUSE_BUTTON_NAME_BUF_LEN]) {
    switch(event.button.button) {
    case SDL_BUTTON_LEFT:
        strncpy(buffer, "Left click", MOUSE_BUTTON_NAME_BUF_LEN);
        break;
    case SDL_BUTTON_MIDDLE:
        strncpy(buffer, "Middle click", MOUSE_BUTTON_NAME_BUF_LEN);
        break;
    case SDL_BUTTON_RIGHT:
        strncpy(buffer, "Right click", MOUSE_BUTTON_NAME_BUF_LEN);
        break;
    case SDL_BUTTON_X1:
        strncpy(buffer, "Side click 1", MOUSE_BUTTON_NAME_BUF_LEN);
        break;
    case SDL_BUTTON_X2:
        strncpy(buffer, "Side click 1", MOUSE_BUTTON_NAME_BUF_LEN);
        break;
    default:
        throw std::runtime_error("This shouldn't happen");
    }
}

int main() {
    // create a window
    window = SDL_CreateWindow("Hello, streaming texture!", WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);

    // get renderer
    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        SDL_Log("Couldn't get renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // create texture
    texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STATIC, // SDL_TEXTUREACCESS_STREAMING,
        WIDTH,
        HEIGHT
    );
    if (!texture) {
        SDL_Log("Couldn't create texture: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // populate the pixels buffer
    populate_pixels();

    // update the texture
    SDL_UpdateTexture(
        texture,                 // the texture to update.
        NULL,                    // an SDL_Rect structure representing the area to update, or NULL to update the entire texture.
        pixels,                  // the raw pixel data in the format of the texture.
        WIDTH * sizeof(uint32_t) // the number of bytes in a row of pixel data, including padding between lines.
    );

    // render in the init func, because we're not changing the texture in this program
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    // main loop
    bool game_is_still_running = true;
    while (game_is_still_running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {  // poll until all events are handled!
            if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED || event.type == SDL_EVENT_QUIT) {
                game_is_still_running = false;
            } else if (event.type == SDL_EVENT_MOUSE_MOTION) {
                // SDL_Log("Mouse motion: (%f, %f)", event.motion.x, event.motion.y);
            } else if (event.type == SDL_EVENT_KEY_DOWN || event.type == SDL_EVENT_KEY_UP) {
                const char* key_name = SDL_GetKeyName(event.key.key);
                SDL_Log("Keyboard: %s (%s)", key_name, event.type == SDL_EVENT_KEY_DOWN ? "down" : "up");
            } else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN || event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
                char button_name[MOUSE_BUTTON_NAME_BUF_LEN] = {0};
                get_mouse_button_name(event, button_name);
                SDL_Log("Mouse click: (%f, %f) - %s (%s)", event.button.x, event.button.y, button_name, event.type == SDL_EVENT_MOUSE_BUTTON_DOWN ? "down" : "up");
            } else if (event.type == SDL_EVENT_MOUSE_WHEEL) {
                SDL_Log("Mouse wheel: scroll (%.2f, %.2f), direction %i, mouse coord (%f, %f), ticks (%i, %i)",
                    event.wheel.x, event.wheel.y,
                    event.wheel.direction,
                    event.wheel.mouse_x, event.wheel.mouse_y,
                    event.wheel.integer_x, event.wheel.integer_y
                );
            }
        }
    }

    // exit
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
