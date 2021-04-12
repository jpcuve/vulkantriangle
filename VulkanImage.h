//
// Created by jpc on 12/04/21.
//

#ifndef VULKANTEST_VULKANIMAGE_H
#define VULKANTEST_VULKANIMAGE_H


#include <vulkan/vulkan.h>
#include "VulkanDevice.h"

class VulkanImage {
private:
    VulkanDevice & logicalDevice;
    VkImageView imageView{};
public:
    VulkanImage(VulkanDevice & device, VkImage image, VkFormat format);
    ~VulkanImage();
    VkImageView getImageView(){ return imageView; }
};


#endif //VULKANTEST_VULKANIMAGE_H
