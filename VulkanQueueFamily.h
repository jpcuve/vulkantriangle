//
// Created by jpc on 12/04/21.
//

#ifndef VULKANTEST_VULKANQUEUEFAMILY_H
#define VULKANTEST_VULKANQUEUEFAMILY_H


#include <cstdint>
#include <vulkan/vulkan.h>

class VulkanQueueFamily {
private:
    uint32_t index;
    VkQueueFamilyProperties properties;
public:
    VulkanQueueFamily(uint32_t index, VkQueueFamilyProperties properties);
    uint32_t getIndex(){ return index; }
    bool isGraphics(){ return properties.queueFlags & VK_QUEUE_GRAPHICS_BIT; }
    bool isCompute(){ return properties.queueFlags & VK_QUEUE_COMPUTE_BIT; }
};


#endif //VULKANTEST_VULKANQUEUEFAMILY_H
