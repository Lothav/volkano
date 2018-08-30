//
// Created by luiz0tavio on 8/30/18.
//

#include "Debug.hpp"

PFN_vkCreateDebugUtilsMessengerEXT  vkn::Debug::CreateDebugUtilsMessengerEXT;
PFN_vkDestroyDebugUtilsMessengerEXT vkn::Debug::DestroyDebugUtilsMessengerEXT;
VkDebugUtilsMessengerEXT            vkn::Debug::dbg_messenger;

void vkn::Debug::init()
{

    // Setup our pointers to the VK_EXT_debug_utils commands
    CreateDebugUtilsMessengerEXT  = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(Instance::instance, "vkCreateDebugUtilsMessengerEXT");
    DestroyDebugUtilsMessengerEXT = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(Instance::instance, "vkDestroyDebugUtilsMessengerEXT");

    PFN_vkDebugUtilsMessengerCallbackEXT debug_messenger_callback = [](
            VkDebugUtilsMessageSeverityFlagBitsEXT       messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT              messageType,
            const VkDebugUtilsMessengerCallbackDataEXT*  pCallbackData,
            void*                                        pUserData) -> VkBool32
    {
        if(messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT)      std::cout << "VERBOSE: ";
        else if(messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT)    std::cout << "INFO: ";
        else if(messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) std::cout << "WARNING: ";
        else if(messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)   std::cout << "ERROR: ";
        else std::cout << "UNKNOWN: ";

        std::cout << pCallbackData->pMessage << std::endl;

        return VK_FALSE;
    };

    // Create a Debug Utils Messenger that will trigger our callback for any warning or error.
    VkDebugUtilsMessengerCreateInfoEXT dbg_messenger_create_info;
    dbg_messenger_create_info.sType                 = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    dbg_messenger_create_info.pNext                 = nullptr;
    dbg_messenger_create_info.flags                 = 0;
    dbg_messenger_create_info.pfnUserCallback       = debug_messenger_callback;
    dbg_messenger_create_info.pUserData             = nullptr;
    dbg_messenger_create_info.messageSeverity       =
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    dbg_messenger_create_info.messageType           =
            VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

    VkResult result = CreateDebugUtilsMessengerEXT(Instance::instance, &dbg_messenger_create_info, nullptr, &dbg_messenger);
    assert(result == VK_SUCCESS);
}

void vkn::Debug::destroy()
{
    DestroyDebugUtilsMessengerEXT(Instance::instance, dbg_messenger, nullptr);
}