//
// Created by jpc on 21/06/21.
//

#include "Instance.h"
#include "PhysicalDevice.h"
#include "PhysicalDeviceList.h"
#include <iostream>

vulkan::Instance::Instance(std::vector<const char *> &extensionNames) {
    VkApplicationInfo appInfo = {
            .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
            .pApplicationName = nullptr,
            .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
            .pEngineName = nullptr,
            .engineVersion = VK_MAKE_VERSION(1, 0, 0),
            .apiVersion = VK_API_VERSION_1_0
    };
    VkInstanceCreateInfo createInfo = {
            .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
            .pApplicationInfo = &appInfo,
            .enabledExtensionCount = static_cast<uint32_t >(extensionNames.size()),
            .ppEnabledExtensionNames = extensionNames.data()
    };
#ifndef NDEBUG
    std::vector<const char *> validationLayers {
            "VK_LAYER_KHRONOS_validation"
    };
    createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
    createInfo.ppEnabledLayerNames = validationLayers.data();
#endif
    if (vkCreateInstance(&createInfo, nullptr, &handle) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create Vulkan instance");
    }
    PhysicalDeviceList physicalDevices {handle};
#ifndef NDEBUG
    for (auto &physicalDevice: physicalDevices.devices){
        std::cout << physicalDevice << std::endl;
    }
#endif
}

vulkan::Instance &vulkan::Instance::operator=(vulkan::Instance &&that) {
    handle = that.handle;
    that.handle = VK_NULL_HANDLE;
    return *this;
}

vulkan::Instance::~Instance() {
    if (handle != VK_NULL_HANDLE) {
        vkDestroyInstance(handle, nullptr);
    }
}

