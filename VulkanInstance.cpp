//
// Created by jpc on 3/04/21.
//

#include <iostream>
#include "VulkanInstance.h"
#include "macros.h"

VulkanInstance::VulkanInstance(const std::string& applicationName) {
    DEBUG("Creating vulkan instance");
    auto appInfo = VkApplicationInfo{
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = applicationName.c_str(),
        .engineVersion = VK_MAKE_VERSION(1, 0, 0),
        .apiVersion = VK_API_VERSION_1_0
    };
    uint32_t glfwExtensionCount = 0;
    auto glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    auto createInfo = VkInstanceCreateInfo{
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &appInfo,
        .enabledExtensionCount = glfwExtensionCount,
        .ppEnabledExtensionNames = glfwExtensions
    };
#ifndef NDEBUG
    const std::vector<const char *> validationLayers = {"VK_LAYER_KHRONOS_validation"};
    createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
    createInfo.ppEnabledLayerNames = validationLayers.data();
    std::cout << "Vulkan validation layer enabled" << std::endl;
#endif
    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create Vulkan instance");
    }
    uint32_t physicalDeviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr);
    if (physicalDeviceCount == 0) {
        throw std::runtime_error("No physical device with Vulkan support");
    }
    VkPhysicalDevice pPhysicalDevices[physicalDeviceCount];
    vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, pPhysicalDevices);
    physicalDevices = std::vector<VulkanPhysicalDevice>(physicalDeviceCount);
    for (size_t i = 0; i < physicalDeviceCount; i++) {
        VkPhysicalDeviceProperties physicalDeviceProperties;
        vkGetPhysicalDeviceProperties(pPhysicalDevices[i], &physicalDeviceProperties);
        VkPhysicalDeviceFeatures physicalDeviceFeatures;
        vkGetPhysicalDeviceFeatures(pPhysicalDevices[i], &physicalDeviceFeatures);
        physicalDevices.emplace_back(pPhysicalDevices[i], physicalDeviceProperties, physicalDeviceFeatures);
    }
    DEBUG("Vulkan instance created");
}

VulkanInstance::~VulkanInstance() {
    DEBUG("Destroying vulkan instance");
    vkDestroyInstance(instance, nullptr);
    DEBUG("Vulkan instance destroyed");
}