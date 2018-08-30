//
// Created by luiz0tavio on 8/30/18.
//

#include "Device.hpp"
#include <memory>
#include <cassert>
#include <iostream>
#include <climits>
#include "Instance.hpp"

VkDevice                                vkn::Device::device;
VkPhysicalDevice                        vkn::Device::physical_device;
VkPhysicalDeviceMemoryProperties 	    vkn::Device::memory_properties;
std::vector<VkQueueFamilyProperties>    vkn::Device::queue_family_props;
uint32_t 						        vkn::Device::queue_family_count;
u_int32_t                               vkn::Device::queue_graphic_family_index = UINT_MAX;
u_int32_t                               vkn::Device::queue_compute_family_index = UINT_MAX;

void vkn::Device::init()
{
    std::vector<VkPhysicalDevice> gpu_vector;
    VkResult res = vkEnumeratePhysicalDevices(Instance::instance, &queue_family_count, nullptr);
    assert(res == VK_SUCCESS && queue_family_count);
    gpu_vector.resize(queue_family_count);
    res = vkEnumeratePhysicalDevices(Instance::instance, &queue_family_count, gpu_vector.data());
    assert(res == VK_SUCCESS);

    vkGetPhysicalDeviceQueueFamilyProperties(gpu_vector[0], &queue_family_count, nullptr);
    assert(queue_family_count >= 1);

    queue_family_props.resize(queue_family_count);
    vkGetPhysicalDeviceQueueFamilyProperties(gpu_vector[0], &queue_family_count, queue_family_props.data());
    assert(queue_family_count >= 1);

    vkGetPhysicalDeviceMemoryProperties(gpu_vector[0], &memory_properties);

    std::cout << "========================================================" << std::endl;
    std::cout << "Devices found:" << std::endl;
    for (uint i = 0; i < gpu_vector.size(); i++) {
        VkPhysicalDeviceProperties device_properties;
        vkGetPhysicalDeviceProperties(gpu_vector[i], &device_properties);
        std::cout << "\tDevice[" << i << "]: " << device_properties.deviceName << std::endl;
        std::cout << "\t\tType: " << device_properties.deviceType << std::endl;
        std::cout << "\t\tAPI: " << (device_properties.apiVersion >> 22) << "." << ((device_properties.apiVersion >> 12) & 0x3ff) << "." << (device_properties.apiVersion & 0xfff) << std::endl;
    }
    uint gpu_index = 0;
    std::cout << "Using Device[" << std::to_string(gpu_index) << "]" << std::endl;
    std::cout << "========================================================" << std::endl;

    physical_device = gpu_vector[gpu_index];

    bool foundGraphic = false;
    bool foundCompute = false;
    for (unsigned int i = 0; i < queue_family_count; i++) {
        if (queue_family_props[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            queue_graphic_family_index = i;
            foundGraphic = true;
        }

        // Some GPU's have a dedicate compute queue. Try to find it.
        if ((queue_family_props[i].queueFlags & VK_QUEUE_COMPUTE_BIT) && ((queue_family_props[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) == 0)) {
            queue_compute_family_index = i;
            foundCompute = true;
        }
    }

    // If no able to find a compute queue dedicated one, find a generic that support compute.
    if (!foundCompute) {
        for (unsigned int i = 0; i < queue_family_count; i++) {
            if (queue_family_props[i].queueFlags & VK_QUEUE_COMPUTE_BIT) {
                queue_compute_family_index = i;
                foundCompute = true;
            }
        }
    }

    assert(foundGraphic && foundCompute && queue_compute_family_index != UINT_MAX && queue_graphic_family_index != UINT_MAX);

    float queue_priorities[1] = {0.0};

    VkDeviceQueueCreateInfo queue_info = {};
    queue_info.sType 			= VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_info.pNext 			= nullptr;
    queue_info.queueCount 		= 1;
    queue_info.pQueuePriorities = queue_priorities;
    queue_info.queueFamilyIndex = queue_graphic_family_index;

    std::vector<const char *> device_extension_names;
    device_extension_names.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);

    VkDeviceCreateInfo device_info = {};
    device_info.sType 					= VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    device_info.pNext 					= nullptr;
    device_info.queueCreateInfoCount 	= 1;
    device_info.pQueueCreateInfos 		= &queue_info;
    device_info.enabledExtensionCount 	= (uint32_t)device_extension_names.size();
    device_info.ppEnabledExtensionNames = device_extension_names.data();
    device_info.enabledLayerCount 		= 0;
    device_info.ppEnabledLayerNames 	= nullptr;
    device_info.pEnabledFeatures 		= nullptr;

    res = vkCreateDevice(physical_device, &device_info, nullptr, &device);
    assert(res == VK_SUCCESS);
}

void vkn::Device::destroy()
{
    vkDestroyDevice(physical_device, nullptr);
}