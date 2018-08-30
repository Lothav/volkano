//
// Created by luiz0tavio on 8/30/18.
//

#ifndef VOLKANO_DEBUG_HPP
#define VOLKANO_DEBUG_HPP

#include <vulkan/vulkan.h>
#include <iostream>
#include <cassert>
#include <mutex>

#include "Instance.hpp"

namespace vkn
{
    class Debug
    {

    private:

        static bool running = false;

        static VkDebugUtilsMessengerEXT dbg_messenger;

        static PFN_vkCreateDebugUtilsMessengerEXT CreateDebugUtilsMessengerEXT;
        static PFN_vkDestroyDebugUtilsMessengerEXT DestroyDebugUtilsMessengerEXT;

        static std::mutex mtx;

    public:

        Debug() = delete;

        static void init();
        static void destroy();
    };
}

#endif //VOLKANO_DEBUG_HPP
