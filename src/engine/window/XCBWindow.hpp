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

        static std::shared_ptr<Window> getInstance();

        const char* getSurface() override;
    };
}

#endif //VOLKANO_XCBWINDOW_HPP
