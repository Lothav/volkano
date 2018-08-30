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

    protected:

        Surface() = default;

        static uint16_t     width;
        static uint16_t     height;
        static VkSurfaceKHR surface;

    public:

        virtual const char* getSurfaceName() { return nullptr; }

        virtual void initWindow() {}
        virtual void initSurface() {}

        virtual void destroyWindow() {}
        virtual void destroySurface() {}

    };
}

#endif //VOLKANO_SURFACE_HPP
