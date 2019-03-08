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
#include <bits/unique_ptr.h>

#define APP_NAME "Volkano"

namespace vkn
{
    typedef struct{
        VkLayerProperties properties = {};
        std::vector<VkExtensionProperties> extensions = {};
    } LayerProperties;

    class Instance
    {

    private:

        /*
         * ADD HERE THE DESIRED LAYERS
         * It will only be initiate if driver supports it
         * */
        constexpr static std::array<const char *, 1> DESIRED_LAYERS = {
            "VK_LAYER_LUNARG_standard_validation"
        };

        static VkInstance instance;

    public:

        Instance() = delete;

        static void init();
        static void destroy();
        static VkInstance getInstance();

    private:

        static std::vector<const char *> getExtensionsNames();
        static std::vector<const char *> getLayersNames();
        static void setGlobalExtensionProperties(LayerProperties* layer_props);

    };
}

#endif //VOLKANO_INSTANCE_HPP
