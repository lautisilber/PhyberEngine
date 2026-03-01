#include <SDL3/SDL.h>

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

#define WIDTH 960
#define HEIGHT 540

// SDL_PIXELFORMAT_RGBA8888
uint32_t pixels[HEIGHT * WIDTH * 4];

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* texture;

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

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv)
{
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

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    // close the window on request
    if (event->type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
    {
        return SDL_APP_SUCCESS;
    }

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
