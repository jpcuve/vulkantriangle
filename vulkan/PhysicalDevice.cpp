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
#ifndef NDEBUG
        std::cout << "Physical device: " << properties.deviceName << std::endl;
#endif
    }
}

