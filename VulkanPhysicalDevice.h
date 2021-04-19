//
// Created by jpc on 4/04/21.
//

#ifndef VULKANTEST_VULKANPHYSICALDEVICE_H
#define VULKANTEST_VULKANPHYSICALDEVICE_H

#include <vulkan/vulkan.h>
#include <vector>
#include <set>
#include "VulkanQueueFamily.h"

class VulkanPhysicalDevice {
private:
    VkPhysicalDevice device{};
    VkPhysicalDeviceProperties physicalDeviceProperties{};
    VkPhysicalDeviceFeatures physicalDeviceFeatures{};
    std::vector<VulkanQueueFamily> queueFamilies;
public:
    VulkanPhysicalDevice()= default;
    VulkanPhysicalDevice(VkPhysicalDevice device, VkPhysicalDeviceProperties properties, VkPhysicalDeviceFeatures features);
    VkPhysicalDevice getDevice() {return device;}
    VkPhysicalDeviceProperties getProperties(){return physicalDeviceProperties;}
    VkPhysicalDeviceFeatures getFeatures(){return physicalDeviceFeatures;}
    const char *getName(){return physicalDeviceProperties.deviceName;}
    std::vector<VulkanQueueFamily> getQueueFamilies() { return queueFamilies; }
};


#endif //VULKANTEST_VULKANPHYSICALDEVICE_H
