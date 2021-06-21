//
// Created by jpc on 21/06/21.
//

#include <iostream>
#include "PhysicalDevice.h"

vulkan::PhysicalDevice::PhysicalDevice(): PhysicalDevice(VK_NULL_HANDLE) {
}

vulkan::PhysicalDevice::PhysicalDevice(VkPhysicalDevice h): handle(h) {
    if (handle != VK_NULL_HANDLE){
        vkGetPhysicalDeviceProperties(handle, &properties);
        vkGetPhysicalDeviceFeatures(handle, &features);
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(handle, &queueFamilyCount, nullptr);
        queueFamilyProperties = std::vector<VkQueueFamilyProperties> {queueFamilyCount};
        vkGetPhysicalDeviceQueueFamilyProperties(handle, &queueFamilyCount, queueFamilyProperties.data());
#ifndef NDEBUG
        std::cout << "Physical device: " << properties.deviceName << std::endl;
#endif
    }
}

bool vulkan::PhysicalDevice::is_suitable() {
    return false;
}

