//
// Created by jpc on 4/04/21.
//

#ifndef VULKANTEST_VULKANPHYSICALDEVICE_H
#define VULKANTEST_VULKANPHYSICALDEVICE_H

#include <vulkan/vulkan.h>
#include <vector>
#include <set>

class VulkanPhysicalDevice {
private:
    VkPhysicalDevice device{};
    VkPhysicalDeviceProperties physicalDeviceProperties{};
    VkPhysicalDeviceFeatures physicalDeviceFeatures{};
    std::vector<VkQueueFamilyProperties> queueFamilyProperties;
public:
    explicit VulkanPhysicalDevice(VkPhysicalDevice device);
    VkPhysicalDevice getDevice() {return device;}
    VkPhysicalDeviceProperties getProperties(){return physicalDeviceProperties;}
    VkPhysicalDeviceFeatures getFeatures(){return physicalDeviceFeatures;}
    const char *getName(){return physicalDeviceProperties.deviceName;}
    std::vector<VkQueueFamilyProperties> getQueueFamilyProperties(){return queueFamilyProperties;}
    std::set<uint32_t> getQueueFamilyIndices(VkQueueFlagBits bits);
};


#endif //VULKANTEST_VULKANPHYSICALDEVICE_H
