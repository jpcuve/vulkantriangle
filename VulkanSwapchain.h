//
// Created by jpc on 7/04/21.
//

#ifndef VULKANTEST_VULKANSWAPCHAIN_H
#define VULKANTEST_VULKANSWAPCHAIN_H

#include <vulkan/vulkan.h>
#include "VulkanImage.h"

class VulkanSwapchain {
private:
    VkDevice device;
    VkSurfaceKHR surface;
public:
    VulkanSwapchain(VkDevice device, VkSurfaceKHR surface);
    ~VulkanSwapchain();
};


#endif //VULKANTEST_VULKANSWAPCHAIN_H
