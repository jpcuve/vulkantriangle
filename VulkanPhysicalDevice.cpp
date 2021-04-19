//
// Created by jpc on 4/04/21.
//

#include <iostream>
#include "VulkanPhysicalDevice.h"
#include "macros.h"

VulkanPhysicalDevice::VulkanPhysicalDevice(
        VkPhysicalDevice device,
        VkPhysicalDeviceProperties properties,
        VkPhysicalDeviceFeatures features):
        device(device),
        physicalDeviceProperties(properties),
        physicalDeviceFeatures(features) {
    DEBUG("Creating physical device");
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
    VkQueueFamilyProperties queueFamilyProperties[queueFamilyCount];
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilyProperties);
    for (size_t i = 0; i < queueFamilyCount; i++){
        queueFamilies.emplace_back(i, queueFamilyProperties[i]);
    }
    DEBUG("Physical device created");
}
