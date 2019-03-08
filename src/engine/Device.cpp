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

void vkn::Device::init()
{
    findPhysicalDevice();
    setFamilyAndMemoryProperties();

    float queue_priorities[1] = {0.0};

    std::vector<const char *> device_extension_names;
    device_extension_names.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);

    VkDeviceQueueCreateInfo queue_info = {};
    queue_info.sType 			= VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_info.pNext 			= nullptr;
    queue_info.queueCount 		= 1;
    queue_info.pQueuePriorities = queue_priorities;
    queue_info.queueFamilyIndex = queue_graphic_family_index;

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

    VkResult res = vkCreateDevice(physical_device, &device_info, nullptr, &device);
    assert(res == VK_SUCCESS);
}

void vkn::Device::destroy()
{
    vkDeviceWaitIdle(device);
    vkDestroyDevice(device, nullptr);
}

void vkn::Device::findPhysicalDevice()
{
    std::vector<VkPhysicalDevice> gpu_vector;
    VkResult res = vkEnumeratePhysicalDevices(Instance::getInstance(), &queue_family_count, nullptr);
    assert(res == VK_SUCCESS && queue_family_count);
    gpu_vector.resize(queue_family_count);
    res = vkEnumeratePhysicalDevices(Instance::getInstance(), &queue_family_count, gpu_vector.data());
    assert(res == VK_SUCCESS);

    uint gpu_index = 0;

    assert(gpu_vector.size() > gpu_index);

    std::cout << "========================================================" << std::endl;
    std::cout << "Devices found:" << std::endl;
    for (uint i = 0; i < gpu_vector.size(); i++) {
        VkPhysicalDeviceProperties device_properties;
        vkGetPhysicalDeviceProperties(gpu_vector[i], &device_properties);
        std::cout << "\tDevice[" << i << "]: " << device_properties.deviceName << std::endl;
        std::cout << "\t\tType: " << device_properties.deviceType << std::endl;
        std::cout << "\t\tAPI: " << (device_properties.apiVersion >> 22) << "." << ((device_properties.apiVersion >> 12) & 0x3ff) << "." << (device_properties.apiVersion & 0xfff) << std::endl;
    }
    std::cout << "Using Device[" << std::to_string(gpu_index) << "]" << std::endl;
    std::cout << "========================================================" << std::endl;

    physical_device = gpu_vector[gpu_index];
}

void vkn::Device::setFamilyAndMemoryProperties()
{
    vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_family_count, nullptr);
    assert(queue_family_count > 0);

    queue_family_props.resize(queue_family_count);
    vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_family_count, queue_family_props.data());
    assert(queue_family_count > 0);

    vkGetPhysicalDeviceMemoryProperties(physical_device, &memory_properties);

    bool foundGraphic = false;
    for (uint8_t i = 0; i < queue_family_count; i++) {
        if (queue_family_props[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            queue_graphic_family_index = i;
            foundGraphic = true;
            break;
        }
    }

    assert(foundGraphic && queue_graphic_family_index != UINT_MAX);
}