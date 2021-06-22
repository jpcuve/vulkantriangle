//
// Created by jpc on 21/06/21.
//

#ifndef VULKANTEST_PHYSICALDEVICE_H
#define VULKANTEST_PHYSICALDEVICE_H

#include <vulkan/vulkan_core.h>
#include <vector>
#include <iostream>
#include "../Surface.h"

namespace vulkan {
    class PhysicalDevice;
}

std::ostream &operator<<(std::ostream& os, const vulkan::PhysicalDevice& that);

namespace vulkan {
    enum QueueType {
        GRAPHICS, COMPUTE, PRESENT
    };

    class PhysicalDevice {
    private:
        VkPhysicalDevice handle {VK_NULL_HANDLE};
        VkPhysicalDeviceProperties properties {};
        VkPhysicalDeviceFeatures features {};
        std::vector<VkQueueFamilyProperties> queueFamilyProperties;
    public:
        PhysicalDevice();
        explicit PhysicalDevice(VkPhysicalDevice handle);
        std::vector<uint32_t> family_indices(QueueType queueType, Surface &surface);
        friend std::ostream &::operator<<(std::ostream& os, const vulkan::PhysicalDevice& that);
    };
}


#endif //VULKANTEST_PHYSICALDEVICE_H
