//
// Created by jpc on 4/04/21.
//

#ifndef VULKANTEST_VULKANDEVICE_H
#define VULKANTEST_VULKANDEVICE_H

#include <vulkan/vulkan.h>
#include "VulkanPhysicalDevice.h"

class VulkanDevice {
private:
    VkDevice logicalDevice{};
    VulkanPhysicalDevice & physicalDevice;
public:
    explicit VulkanDevice(VulkanPhysicalDevice & device);
    ~VulkanDevice();
    VkDevice & getDevice(){ return logicalDevice; }
    VulkanPhysicalDevice & getPhysicalDevice() { return physicalDevice; }
};


#endif //VULKANTEST_VULKANDEVICE_H
