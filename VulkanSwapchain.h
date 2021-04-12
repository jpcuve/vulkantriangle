//
// Created by jpc on 7/04/21.
//

#ifndef VULKANTEST_VULKANSWAPCHAIN_H
#define VULKANTEST_VULKANSWAPCHAIN_H

#include <vulkan/vulkan.h>
#include "VulkanDevice.h"
#include "VulkanImage.h"

class VulkanSwapchain {
private:
    VulkanDevice & logicalDevice;
    VkSwapchainKHR swapChain;
    std::vector<VulkanImage> images;
public:
    VulkanSwapchain(VulkanDevice & device, VkSurfaceKHR & surface);
    ~VulkanSwapchain();
    std::vector<VulkanImage> getImages(){ return images; }
};


#endif //VULKANTEST_VULKANSWAPCHAIN_H
