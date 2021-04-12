//
// Created by jpc on 7/04/21.
//

#ifndef VULKANTEST_VULKANSWAPCHAIN_H
#define VULKANTEST_VULKANSWAPCHAIN_H

#include <vulkan/vulkan.h>
#include "VulkanDevice.h"

class VulkanSwapchain {
private:
    VulkanDevice & logicalDevice;
    VkSwapchainKHR swapChain;
    std::vector<VkImage> images;
public:
    VulkanSwapchain(VulkanDevice & device, VkSurfaceKHR & surface);
    ~VulkanSwapchain();
    std::vector<VkImage> getImages(){ return images; }
};


#endif //VULKANTEST_VULKANSWAPCHAIN_H
