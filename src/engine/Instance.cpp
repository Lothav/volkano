//
// Created by luiz0tavio on 8/30/18.
//

#include "Instance.hpp"

VkInstance vkn::Instance::instance;
constexpr std::array<const char *, 1> vkn::Instance::DESIRED_LAYERS;

void vkn::Instance::init()
{
    auto layers_names = getLayersNames();
    std::cout << "Using Layers:" << std::endl;
    for(auto i : layers_names) {
        std::cout << i << std::endl;
    }

    setGlobalExtensionProperties(nullptr);
    auto extensions_names = getExtensionsNames();
    std::cout << "Using Extensions:" << std::endl;
    for(auto i : extensions_names) {
        std::cout << i << std::endl;
    }

    VkApplicationInfo app_info = {};
    app_info.sType 				= VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pNext 				= nullptr;
    app_info.pApplicationName 	= APP_NAME;
    app_info.applicationVersion = 1;
    app_info.pEngineName 		= APP_NAME;
    app_info.engineVersion 		= 1;
    app_info.apiVersion 		= VK_API_VERSION_1_0;

    VkInstanceCreateInfo inst_info = {};
    inst_info.sType 					= VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    inst_info.pNext 					= nullptr;
    inst_info.flags 					= 0;
    inst_info.pApplicationInfo 		    = &app_info;
    inst_info.enabledLayerCount 		= (uint32_t) layers_names.size();
    inst_info.ppEnabledLayerNames 		= layers_names.size() ? layers_names.data() : nullptr;
    inst_info.enabledExtensionCount 	= (uint32_t) extensions_names.size();
    inst_info.ppEnabledExtensionNames 	= extensions_names.data();

    VkResult res = vkCreateInstance(&inst_info, nullptr, &instance);
    assert(res == VK_SUCCESS);
}

void vkn::Instance::destroy()
{
    vkDestroyInstance(instance, nullptr);
}

std::vector<const char *> vkn::Instance::getExtensionsNames()
{
    std::vector<const char *> _instance_extension_names;
    _instance_extension_names.emplace_back(VK_KHR_SURFACE_EXTENSION_NAME);
    _instance_extension_names.emplace_back(vkn::Window::getSurfaceName());

#ifdef DEBUG
    _instance_extension_names.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif
    return _instance_extension_names;
}

std::vector<const char *> vkn::Instance::getLayersNames()
{
    std::vector<LayerProperties> layer_props_v;

    uint32_t instance_layer_count;
    VkResult res;

    std::vector<VkLayerProperties> vk_props = {};

    do {
        res = vkEnumerateInstanceLayerProperties(&instance_layer_count, nullptr);
        if (res) break;
        if (instance_layer_count == 0) break;
        vk_props.resize(instance_layer_count);
        res = vkEnumerateInstanceLayerProperties(&instance_layer_count, vk_props.data());
    } while (res == VK_INCOMPLETE);

    for (uint32_t i = 0; i < instance_layer_count; i++) {

        LayerProperties layer_props;
        layer_props.properties = vk_props[i];
        setGlobalExtensionProperties(&layer_props);

        layer_props_v.push_back(layer_props);
    }

    assert(res == VK_SUCCESS);

    std::cout << "Layers available:" << std::endl;
    std::vector<const char *> layer_names;
    for(auto i : layer_props_v) {
        std::cout << i.properties.layerName << std::endl;
        for(auto j : Instance::DESIRED_LAYERS) {
            if(0 == strcmp(j, i.properties.layerName)) {
                layer_names.push_back(j);
            }
        }
    }

    return layer_names;
}

void vkn::Instance::setGlobalExtensionProperties(LayerProperties* layer_props)
{
    VkExtensionProperties *instance_extensions;
    uint32_t instance_extension_count;

    char *layer_name = layer_props != nullptr ? layer_props->properties.layerName : nullptr;

    VkResult res;
    do {
        res = vkEnumerateInstanceExtensionProperties(layer_name, &instance_extension_count, nullptr);
        assert(res == VK_SUCCESS);

        if (instance_extension_count == 0) break;

        std::vector<VkExtensionProperties> extensions;
        if(layer_props != nullptr){
            layer_props->extensions.resize(instance_extension_count);
            instance_extensions = layer_props->extensions.data();
        } else {
            extensions.resize(instance_extension_count);
            instance_extensions = extensions.data();
        }

        res = vkEnumerateInstanceExtensionProperties(layer_name, &instance_extension_count, instance_extensions);

    } while (res == VK_INCOMPLETE);

    assert(res == VK_SUCCESS);
}