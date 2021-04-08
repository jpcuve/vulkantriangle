//
// Created by jpc on 3/04/21.
//

#ifndef VULKANTEST_VULKANINSTANCE_H
#define VULKANTEST_VULKANINSTANCE_H

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <string>
#include "VulkanPhysicalDevice.h"

class VulkanInstance {
private:
    VkInstance instance{};
    std::vector<VulkanPhysicalDevice> physicalDevices;
public:
    explicit VulkanInstance(const std::string& applicationName);
    ~VulkanInstance();
    VkInstance getInstance() { return instance; }
    std::vector<VulkanPhysicalDevice> getPhysicalDevices(){return physicalDevices;}
};


#endif //VULKANTEST_VULKANINSTANCE_H
