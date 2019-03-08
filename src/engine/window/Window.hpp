//
// Created by luiz0tavio on 8/30/18.
//

#ifndef VOLKANO_WINDOW_HPP
#define VOLKANO_WINDOW_HPP

#include "SDL.h"
#include "SDL_vulkan.h"

#include <memory>
#include <cassert>
#include <iostream>
#include "Surface.hpp"

namespace vkn
{
    class Window
    {

    private:

        static std::shared_ptr<Surface> surface;
        static SDL_Window* window;

    public:

        static void init();
        static void destroy();

        static SDL_Window* getWindow();

    };
}

#endif //VOLKANO_WINDOW_HPP
