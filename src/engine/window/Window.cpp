//
// Created by luiz0tavio on 8/30/18.
//

#include "Window.hpp"

std::shared_ptr<vkn::Surface> vkn::Window::surface;
SDL_Window* vkn::Window::window;

void vkn::Window::init()
{
    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return;
    }

    // Setup window
    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);
    auto window_flags = (SDL_WindowFlags)(SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

    window = SDL_CreateWindow("Hell Yeah!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
}

void vkn::Window::destroy()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Window* vkn::Window::getWindow()
{
    return window;
}
