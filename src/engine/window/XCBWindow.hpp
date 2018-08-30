//
// Created by luiz0tavio on 8/30/18.
//

#ifndef VOLKANO_XCBWINDOW_HPP
#define VOLKANO_XCBWINDOW_HPP

#include "Window.hpp"
#include <memory>
#include <vulkan/vulkan.h>

namespace vkn
{
    class XCBWindow : Window
    {

    private:

        static std::shared_ptr<Window> class_instance;

        XCBWindow() = default;

    public:

        static std::shared_ptr<Window> getInstance()
        {
            if (class_instance == nullptr) {
                std::shared_ptr<Window> window_s_ptr (static_cast<Window*>(new XCBWindow()));
                class_instance = std::move(window_s_ptr);
            }

            return class_instance;
        };

        const char* getSurface() override
        {
            return VK_KHR_XCB_SURFACE_EXTENSION_NAME;
        }
    };
}

#endif //VOLKANO_XCBWINDOW_HPP
