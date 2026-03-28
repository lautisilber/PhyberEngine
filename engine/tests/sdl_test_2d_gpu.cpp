#include <SDL3/SDL.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <stdlib.h>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

#define WIDTH 500
#define HEIGHT 400

#ifdef __APPLE__
    #define SDL_SHADERFORMAT SDL_GPU_SHADERFORMAT_METALLIB
    #define SDL_SHADER_EXT ".metallib"
#elif _WIN32
    #define SDL_SHADERFORMAT SDL_GPU_SHADERFORMAT_DXIL
    #define SDL_SHADER_EXT ".dxil"
#else
    #define SDL_SHADERFORMAT SDL_GPU_SHADERFORMAT_SPIRV
    #define SDL_SHADER_EXT ".spv"
#endif

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

SDL_GPUDevice* device = nullptr;
SDL_GPUGraphicsPipeline* pipeline = nullptr;

struct Transform {
    glm::vec3 pos;
    glm::vec3 rot;
    glm::vec3 scale;
};

struct Rect {
    Transform transform;
    glm::vec2 top_left, bottom_right;
    float z;
    uint32_t color;
};

struct RectVertex {
    float pos[2];
    uint32_t color;
};

Rect rect = {
    .transform = {
        .pos = glm::vec3(0),
        .rot = glm::vec3(0),
        .scale = glm::vec3(1)
    },
    .top_left = glm::vec2(-.5, .5),
    .bottom_right = glm::vec2(.5, -.5),
    .color = 0x00FF00FF
};

std::vector<RectVertex> get_rect_vertices(const Rect &rect) {
    const glm::vec2 &tl = rect.top_left;
    const glm::vec2 &br = rect.bottom_right;
    const glm::vec2 tr = glm::vec2(br.x, tl.y);
    const glm::vec2 bl = glm::vec2(tl.x, br.y);
    const uint32_t c = rect.color;
    return {
        {{tl.x, tl.y}, c},
        {{bl.x, bl.y}, c},
        {{tr.x, tr.y}, c},
        {{bl.x, bl.y}, c},
        {{br.x, br.y}, c},
        {{tr.x, tr.y}, c}
    };
}

void abort() {
    printf("%s\n", SDL_GetError());
    exit(1);
}

#define SAFE_SDL(func) do { if (!(func)) { abort(); } } while (0)

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("GPU 2D", WIDTH, HEIGHT, 0);
    if (!window) {
        abort();
    }

    device = SDL_CreateGPUDevice(SDL_SHADERFORMAT, true, nullptr);
    if (!device) {
        abort();
    }

    if (!SDL_ClaimWindowForGPUDevice(device, window)) {
        abort();
    }

    // const fs::path shaders_dir = (fs::path(__FILE__).parent_path() / ".." / "shaders" / "2D_backend").lexically_normal();

    const auto rect_verts = get_rect_vertices(rect);

    bool game_is_still_running = true;
    while (game_is_still_running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                game_is_still_running = false;
            }
        }

        SDL_GPUCommandBuffer* cmd = SDL_AcquireGPUCommandBuffer(device);

        SDL_GPUTexture* swapchain_texture = nullptr;
        if (!SDL_AcquireGPUSwapchainTexture(cmd, window, &swapchain_texture, nullptr, nullptr)) {
            abort();
        }

        // change background color
        SDL_GPUColorTargetInfo color_target = {};
        color_target.texture = swapchain_texture;
        color_target.load_op = SDL_GPU_LOADOP_CLEAR;
        color_target.store_op = SDL_GPU_STOREOP_STORE;
        color_target.clear_color = {0.168f, 0.168f, 0.168f, 1.0f};

        SDL_GPURenderPass* pass =
            SDL_BeginGPURenderPass(cmd, &color_target, 1, nullptr);



        SDL_EndGPURenderPass(pass);
        SDL_SubmitGPUCommandBuffer(cmd);

    }

    SDL_DestroyGPUDevice(device);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
