//
// Created by luiz0tavio on 8/30/18.
//

#ifndef VOLKANO_XCBWINDOW_HPP
#define VOLKANO_XCBWINDOW_HPP

#include "../Instance.hpp"
#include "Surface.hpp"
#include <memory>
#include <vulkan/vulkan.h>
#include <iostream>

namespace vkn
{
    class XCBSurface : Surface
    {

    private:

        static std::shared_ptr<Surface> class_instance;

        xcb_screen_t* 			screen{};
        xcb_window_t 			window{};
        xcb_connection_t*		connection{};

        XCBSurface();

    public:

        static std::shared_ptr<Surface> getInstance();

        void initWindow() override;
        void initSurface() override;
        void destroySurface() override;
        void destroyWindow() override;

        const char* getSurfaceName() override;
    };
}

#endif //VOLKANO_XCBWINDOW_HPP
