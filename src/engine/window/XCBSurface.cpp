//
// Created by luiz0tavio on 8/30/18.
//

#include "XCBSurface.hpp"

std::shared_ptr<vkn::Surface> vkn::XCBSurface::class_instance;

std::shared_ptr<vkn::Surface> vkn::XCBSurface::getInstance()
{
    if (class_instance == nullptr) {
        std::shared_ptr<Surface> window_s_ptr (static_cast<Surface*>(new XCBSurface()));
        class_instance = std::move(window_s_ptr);
    }

    return class_instance;
};

const char* vkn::XCBSurface::getSurfaceName()
{
    return VK_KHR_XCB_SURFACE_EXTENSION_NAME;
}