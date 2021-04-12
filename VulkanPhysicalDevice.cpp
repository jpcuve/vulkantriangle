//
// Created by jpc on 4/04/21.
//

#include <iostream>
#include "VulkanPhysicalDevice.h"

VulkanPhysicalDevice::VulkanPhysicalDevice(VkPhysicalDevice device): device(device) {
    vkGetPhysicalDeviceProperties(device, &physicalDeviceProperties);
    vkGetPhysicalDeviceFeatures(device, &physicalDeviceFeatures);
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
    VkQueueFamilyProperties queueFamilyProperties[queueFamilyCount];
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilyProperties);
    queueFamilies = std::vector<VulkanQueueFamily>();
    for (uint32_t i = 0; i < queueFamilyCount; i++){
        queueFamilies.emplace_back(i, queueFamilyProperties[i]);
    }
#ifndef NDEBUG
    std::cout << "Physical device created" << std::endl;
#endif
}
