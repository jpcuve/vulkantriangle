//
// Created by jpc on 21/06/21.
//

#ifndef VULKANTEST_PHYSICALDEVICE_H
#define VULKANTEST_PHYSICALDEVICE_H

#include <vulkan/vulkan_core.h>

namespace vulkan {
    class PhysicalDevice {
    private:
        VkPhysicalDevice handle {VK_NULL_HANDLE};
        VkPhysicalDeviceProperties properties {};
        VkPhysicalDeviceFeatures features {};
    public:
        PhysicalDevice();
        explicit PhysicalDevice(VkPhysicalDevice handle);

    };
}


#endif //VULKANTEST_PHYSICALDEVICE_H
