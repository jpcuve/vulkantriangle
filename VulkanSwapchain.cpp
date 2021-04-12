//
// Created by jpc on 7/04/21.
//
#include <iostream>
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include "VulkanSwapchain.h"
#include "macros.h"

VulkanSwapchain::VulkanSwapchain(VulkanDevice & device, VkSurfaceKHR & surface): logicalDevice(device) {
    auto physicalDevice = device.getPhysicalDevice();
    for (auto & vulkanQueueFamily: physicalDevice.getQueueFamilies()){
        if (vulkanQueueFamily.isGraphics()){
            VkBool32 presentSupport = VK_FALSE;
            // the next call is necessary but I do not know why
            vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice.getDevice(), vulkanQueueFamily.getIndex(), surface, &presentSupport);
        }
    }
    VkSurfaceCapabilitiesKHR surfaceCapabilities{};
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice.getDevice(), surface, &surfaceCapabilities);
    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice.getDevice(), surface, &formatCount, nullptr);
    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice.getDevice(), surface, &presentModeCount, nullptr);
    if (formatCount == 0 || presentModeCount == 0){
        throw std::runtime_error("Physical device cannot output to display");
    }
    VkSurfaceFormatKHR surfaceFormats[formatCount];
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice.getDevice(), surface, &formatCount, surfaceFormats);
    VkPresentModeKHR presentModes[presentModeCount];
    vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice.getDevice(), surface, &presentModeCount, presentModes);

    // choose format
    uint32_t formatIndex = 0;
    for (uint32_t i = 0; i < formatCount; i++){
        auto & surfaceFormat = surfaceFormats[i];
        if (surfaceFormat.format == VK_FORMAT_B8G8R8A8_SRGB && surfaceFormat.colorSpace == VK_COLORSPACE_SRGB_NONLINEAR_KHR){
            formatIndex = i;
        }
    }
    auto surfaceFormat = surfaceFormats[formatIndex];
    // choose presentation mode
    VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR;  // always present
    for (uint32_t i = 0; i < presentModeCount; i++){
        if (presentModes[i] == VK_PRESENT_MODE_MAILBOX_KHR){
            presentMode = presentModes[i];
        }
    }
    std::cout << "Current extent: " << surfaceCapabilities.currentExtent.width << ", " << surfaceCapabilities.currentExtent.height << std::endl;
    VkSwapchainCreateInfoKHR createInfo{
            .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
            .surface = surface,
            .minImageCount = std::max(surfaceCapabilities.minImageCount + 1, surfaceCapabilities.maxImageCount),
            .imageFormat = surfaceFormat.format,
            .imageColorSpace = surfaceFormat.colorSpace,
            .imageExtent = surfaceCapabilities.currentExtent,  // TODO check this is not UINT32_MAX...?
            .imageArrayLayers = 1,
            .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
            .preTransform = surfaceCapabilities.currentTransform,
            .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
            .presentMode = presentMode,
            .clipped = VK_TRUE,
            .oldSwapchain = VK_NULL_HANDLE,
    };

/*
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
*/
    if (vkCreateSwapchainKHR(logicalDevice.getDevice(), &createInfo, nullptr, &swapChain) != VK_SUCCESS){
        throw std::runtime_error("Failed to create swap chain");
    }
    uint32_t imageCount;
    vkGetSwapchainImagesKHR(device.getDevice(), swapChain, &imageCount, nullptr);
    VkImage is[imageCount];
    vkGetSwapchainImagesKHR(device.getDevice(), swapChain, &imageCount, is);
    for (uint32_t i = 0; i < imageCount; i++){
        images.emplace_back(VulkanImage(device, is[i], surfaceFormat.format));
    }
    DEBUG("Swap chain created");
}

VulkanSwapchain::~VulkanSwapchain() {
    vkDestroySwapchainKHR(logicalDevice.getDevice(), swapChain, nullptr);
    DEBUG("Swap chain destroyed");
}
