//
// Created by jpc on 21/06/21.
//

#include "Instance.h"
#include "PhysicalDevice.h"
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
    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create Vulkan instance");
    }
    uint32_t physicalDeviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr);
    VkPhysicalDevice physicalDevices[physicalDeviceCount];
    vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, physicalDevices);
    std::vector<vulkan::PhysicalDevice> v {physicalDeviceCount};
    for (size_t i = 0; i < physicalDeviceCount; i++){
        v[i] = vulkan::PhysicalDevice {physicalDevices[i]};
    }
}

vulkan::Instance::~Instance() {
    if (instance != VK_NULL_HANDLE) {
        vkDestroyInstance(instance, nullptr);
    }
}