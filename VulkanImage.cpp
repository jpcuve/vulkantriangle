//
// Created by jpc on 12/04/21.
//

#include <iostream>
#include "VulkanImage.h"
#include "macros.h"

VulkanImage::VulkanImage(VulkanDevice & device, VkImage image, VkFormat format): logicalDevice(device) {
    VkImageViewCreateInfo createInfo {
            .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
            .image = image,
            .viewType = VK_IMAGE_VIEW_TYPE_2D,
            .format = format,
            .components = VkComponentMapping {
                    .r = VK_COMPONENT_SWIZZLE_IDENTITY,
                    .g = VK_COMPONENT_SWIZZLE_IDENTITY,
                    .b = VK_COMPONENT_SWIZZLE_IDENTITY,
                    .a = VK_COMPONENT_SWIZZLE_IDENTITY,
            },
            .subresourceRange = VkImageSubresourceRange {
                    .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                    .baseMipLevel = 0,
                    .levelCount = 1,
                    .baseArrayLayer = 0,
                    .layerCount = 1,
            },
    };
    if (vkCreateImageView(logicalDevice.getDevice(), &createInfo, nullptr, &imageView) != VK_SUCCESS){
        throw std::runtime_error("Failed to create image view");
    }
    DEBUG("Vulkan image created");
}

VulkanImage::~VulkanImage() {
    vkDestroyImageView(logicalDevice.getDevice(), imageView, nullptr);
    DEBUG("Vulkan image destroyed");
}
