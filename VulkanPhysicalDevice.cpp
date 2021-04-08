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
    queueFamilyProperties = std::vector<VkQueueFamilyProperties>(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilyProperties.data());
#ifndef NDEBUG
    std::cout << "Physical device created" << std::endl;
#endif
}

std::set<uint32_t> VulkanPhysicalDevice::getQueueIndices(VkQueueFlagBits bits) {
    std::set<uint32_t> s;
    for (uint32_t i = 0; i < queueFamilyProperties.size(); i++){
        if (queueFamilyProperties[i].queueFlags & bits){
            s.insert(i);
        }
    }
    return s;
}
