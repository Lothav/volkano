//
// Created by luiz0tavio on 8/31/18.
//

#include "Volkano.hpp"

void vkn::Volkano::init() noexcept
{
    vkn::Window::init();
    vkn::Instance::init();
#ifdef DEBUG
    vkn::Debug::init();
#endif
    vkn::Surface::init();
    vkn::Device::init();
}

void vkn::Volkano::cleanup() noexcept
{
    vkn::Device::destroy();
    vkn::Surface::destroy();
#ifdef DEBUG
    vkn::Debug::destroy();
#endif
    vkn::Instance::destroy();
    vkn::Window::destroy();
}
