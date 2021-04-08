//
// Created by jpc on 7/04/21.
//
#include <iostream>
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include "VulkanSwapchain.h"

VulkanSwapchain::VulkanSwapchain(VulkanDevice & device, VkSurfaceKHR & surface): logicalDevice(device) {
    VkSwapchainCreateInfoKHR createInfo{
            .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
            .surface = surface,
            .minImageCount = imageCount,
            .imageFormat = surfaceFormat.format,
            .imageColorSpace = surfaceFormat.colorSpace,
            .imageExtent = extent,
            .imageArrayLayers = 1,
            .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
            .preTransform = swapChainSupport.capabilities.currentTransform,
            .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
            .presentMode = presentMode,
            .clipped = VK_TRUE,
            .oldSwapchain = VK_NULL_HANDLE,
    };
    QueueFamilyIndices indices = findQueueFamilyIndices(device.getPhysicalDevice());
    if (indices.graphicsFamily != indices.presentFamily){
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    } else {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.queueFamilyIndexCount = 0;
        createInfo.pQueueFamilyIndices = nullptr;
    }
    if (vkCreateSwapchainKHR(logicalDevice.getDevice(), &createInfo, nullptr, &swapChain) != VK_SUCCESS){
        throw std::runtime_error("Failed to create swap chain");
    }
    std::cout << "Swap chain created" << std::endl;
}

VulkanSwapchain::~VulkanSwapchain() {
    vkDestroySwapchainKHR(logicalDevice.getDevice(), swapChain, nullptr);
    std::cout << "Swap chain destroyed" << std::endl;
}
