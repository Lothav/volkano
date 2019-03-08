//
// Created by luiz0tavio on 8/30/18.
//

#include <Instance.hpp>
#include <Debug.hpp>
#include "Surface.hpp"
#include "Window.hpp"

uint16_t vkn::Surface::width;
uint16_t vkn::Surface::height;
VkSurfaceKHR vkn::Surface::surface;

void vkn::Surface::init()
{
    if (SDL_Vulkan_CreateSurface(vkn::Window::getWindow(), vkn::Instance::getInstance(), &surface) == SDL_bool::SDL_FALSE)
    {
        vkn::Debug::logError("Failed to create Vulkan surface.");
        return;
    }
}

void vkn::Surface::destroy()
{

}
