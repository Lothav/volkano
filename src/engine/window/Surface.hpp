//
// Created by luiz0tavio on 8/30/18.
//

#ifndef VOLKANO_SURFACE_HPP
#define VOLKANO_SURFACE_HPP

#include <cstdint>
#include <vulkan/vulkan.h>

namespace vkn
{
    class Surface
    {

    private:

        static uint16_t     width;
        static uint16_t     height;
        static VkSurfaceKHR surface;

    public:

        Surface() = delete;

        static void init();
        static void destroy();

    };
}

#endif //VOLKANO_SURFACE_HPP
