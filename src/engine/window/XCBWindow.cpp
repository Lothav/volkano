//
// Created by luiz0tavio on 8/30/18.
//

#include "XCBWindow.hpp"

std::shared_ptr<vkn::Window> vkn::XCBWindow::class_instance;

std::shared_ptr<vkn::Window> vkn::XCBWindow::getInstance()
{
    if (class_instance == nullptr) {
        std::shared_ptr<Window> window_s_ptr (static_cast<Window*>(new XCBWindow()));
        class_instance = std::move(window_s_ptr);
    }

    return class_instance;
};

const char* vkn::XCBWindow::getSurface()
{
    return VK_KHR_XCB_SURFACE_EXTENSION_NAME;
}