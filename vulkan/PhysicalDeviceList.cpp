//
// Created by jpc on 21/06/21.
//

#include "PhysicalDeviceList.h"

vulkan::PhysicalDeviceList::PhysicalDeviceList(VkInstance instance) {
    uint32_t physicalDeviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr);
    VkPhysicalDevice physicalDevices[physicalDeviceCount];
    vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, physicalDevices);
    devices = std::vector<vulkan::PhysicalDevice> {physicalDeviceCount};
    for (size_t i = 0; i < physicalDeviceCount; i++){
        devices[i] = vulkan::PhysicalDevice {physicalDevices[i]};
    }
}
