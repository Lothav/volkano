//
// Created by luiz0tavio on 8/30/18.
//

#include "Window.hpp"

std::shared_ptr<vkn::Surface> vkn::Window::surface;

void vkn::Window::init()
{
#ifdef VK_USE_PLATFORM_XCB_KHR
    surface = XCBSurface::getInstance();
#else
    std::cerr << "Platform not supported!" << std::endl;
            assert(false);
#endif
}

const char* vkn::Window::getSurfaceName()
{
    if(surface == nullptr) {
        std::cerr << "Surface not initiated!" << std::endl;
        assert(false);
    }

    return surface->getSurfaceName();
}

void vkn::Window::destroy()
{
    // destroy surface
}