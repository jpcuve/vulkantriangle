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
        const char *get_device_name() { return properties.deviceName; }
    };
}

std::ostream &operator<<(std::ostream& os, vulkan::PhysicalDevice that);


#endif //VULKANTEST_PHYSICALDEVICE_H
