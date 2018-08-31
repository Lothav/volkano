//
// Created by luiz0tavio on 8/30/18.
//

#ifndef VOLKANO_DEVICE_HPP
#define VOLKANO_DEVICE_HPP

#include <vulkan/vulkan.h>
#include <vector>

namespace vkn
{
    class Device
    {

    public:

        Device() = delete;

        static VkDevice                                 device;
        static VkPhysicalDevice                         physical_device;
        static VkPhysicalDeviceMemoryProperties 		memory_properties;
        static std::vector<VkQueueFamilyProperties>     queue_family_props;
        static uint32_t 						        queue_family_count;
        static u_int32_t                                queue_graphic_family_index;

        static void init();
        static void destroy();

    private:

        static void setFamilyAndMemoryProperties();
        static void findPhysicalDevice();
    };

}

#endif //VOLKANO_DEVICE_HPP
