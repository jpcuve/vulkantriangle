//
// Created by jpc on 21/06/21.
//

#ifndef VULKANTEST_PHYSICALDEVICE_H
#define VULKANTEST_PHYSICALDEVICE_H

#include <vulkan/vulkan_core.h>
#include <vector>

namespace vulkan {
    class PhysicalDevice {
    private:
        VkPhysicalDevice handle {VK_NULL_HANDLE};
        VkPhysicalDeviceProperties properties {};
        VkPhysicalDeviceFeatures features {};
        std::vector<VkQueueFamilyProperties> queueFamilyProperties;
    public:
        PhysicalDevice();
        explicit PhysicalDevice(VkPhysicalDevice handle);
        bool is_suitable();

    };
}


#endif //VULKANTEST_PHYSICALDEVICE_H
