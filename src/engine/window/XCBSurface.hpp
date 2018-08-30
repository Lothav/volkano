//
// Created by luiz0tavio on 8/30/18.
//

#ifndef VOLKANO_XCBWINDOW_HPP
#define VOLKANO_XCBWINDOW_HPP

#include "Surface.hpp"
#include <memory>
#include <vulkan/vulkan.h>

namespace vkn
{
    class XCBSurface : Surface
    {

    private:

        static std::shared_ptr<Surface> class_instance;

        XCBSurface() = default;

    public:

        static std::shared_ptr<Surface> getInstance();
        const char* getSurfaceName() override;
    };
}

#endif //VOLKANO_XCBWINDOW_HPP
