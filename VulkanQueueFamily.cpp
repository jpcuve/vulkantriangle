//
// Created by jpc on 12/04/21.
//

#include "VulkanQueueFamily.h"
#include "macros.h"
#include <iostream>

VulkanQueueFamily::VulkanQueueFamily(uint32_t index, VkQueueFamilyProperties properties): index(index), properties(properties) {
    DEBUG("Creating queue family");
    DEBUG("Queue family created");
}
