//
// Created by luiz0tavio on 8/30/18.
//

#ifndef VOLKANO_INSTANCE_HPP
#define VOLKANO_INSTANCE_HPP

#include <vulkan/vulkan.h>
#include <cassert>
#include <vector>
#include <iostream>
#include <cstring>

#define APP_NAME "Volkano"

namespace vkn
{
    class Instance
    {

    public:

        static VkInstance instance;

        Instance() = delete;

        static void init()
        {
            //std::vector<const char *> _layer_names = this->getLayerNames();


            std::vector<const char *> _instance_extension_names;
            _instance_extension_names.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
            _instance_extension_names.push_back(VK_KHR_XCB_SURFACE_EXTENSION_NAME);

            std::cout << "Available extensions:" << std::endl;
            uint32_t instance_extension_count = 0;
            auto err = vkEnumerateInstanceExtensionProperties(nullptr, &instance_extension_count, nullptr);
            assert(!err);

            if (instance_extension_count > 0) {
                std::vector<VkExtensionProperties> instance_extensions;
                instance_extensions.resize(instance_extension_count);
                err = vkEnumerateInstanceExtensionProperties(nullptr, &instance_extension_count, instance_extensions.data());
                assert(!err);

                for (const auto& extension : instance_extensions) {
                    std::cout << "\t" << extension.extensionName << std::endl;
                }
            }

            _instance_extension_names.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

            VkApplicationInfo _app_info = {};
            _app_info.sType 				= VK_STRUCTURE_TYPE_APPLICATION_INFO;
            _app_info.pNext 				= nullptr;
            _app_info.pApplicationName 		= APP_NAME;
            _app_info.applicationVersion 	= 1;
            _app_info.pEngineName 			= APP_NAME;
            _app_info.engineVersion 		= 1;
            _app_info.apiVersion 			= VK_API_VERSION_1_0;

            VkInstanceCreateInfo _inst_info = {};
            memset(&_inst_info, 0, sizeof(VkInstanceCreateInfo));
            _inst_info.sType 					= VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            _inst_info.pNext 					= nullptr;
            _inst_info.flags 					= 0;
            _inst_info.pApplicationInfo 		= &_app_info;
            _inst_info.enabledLayerCount 		= (uint32_t) _layer_names.size();
            _inst_info.ppEnabledLayerNames 		= _layer_names.size() ? _layer_names.data() : nullptr;
            _inst_info.enabledExtensionCount 	= (uint32_t) _instance_extension_names.size();
            _inst_info.ppEnabledExtensionNames 	= _instance_extension_names.data();

            VkResult res = vkCreateInstance(&_inst_info, nullptr, &instance);
            assert(res == VK_SUCCESS);
        }

    };
}

#endif //VOLKANO_INSTANCE_HPP
