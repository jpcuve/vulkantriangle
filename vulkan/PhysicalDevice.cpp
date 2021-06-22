//
// Created by jpc on 21/06/21.
//

#include "PhysicalDevice.h"

vulkan::PhysicalDevice::PhysicalDevice(): PhysicalDevice(VK_NULL_HANDLE) {
}

vulkan::PhysicalDevice::PhysicalDevice(VkPhysicalDevice h): handle(h) {
    if (handle != VK_NULL_HANDLE){
        vkGetPhysicalDeviceProperties(handle, &properties);
        vkGetPhysicalDeviceFeatures(handle, &features);
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(handle, &queueFamilyCount, nullptr);
        queueFamilyProperties = std::vector<VkQueueFamilyProperties> {queueFamilyCount};
        vkGetPhysicalDeviceQueueFamilyProperties(handle, &queueFamilyCount, queueFamilyProperties.data());
    }
}

std::vector<uint32_t> vulkan::PhysicalDevice::family_indices(QueueType queueType, Surface &surface) {
    std::vector<uint32_t> ret;
    for (uint32_t i = 0; i < queueFamilyProperties.size(); i++){
        auto &props = queueFamilyProperties[i];
        switch (queueType)  {
            case GRAPHICS:
                if (props.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                    ret.push_back(i);
                }
                break;
            case COMPUTE:
                if (props.queueFlags & VK_QUEUE_COMPUTE_BIT) {
                    ret.push_back(i);
                }
                break;
            case PRESENT:
                VkBool32 presentSupport = VK_FALSE;
                vkGetPhysicalDeviceSurfaceSupportKHR(handle, i, surface.get_handle(), &presentSupport);
                if (presentSupport) {
                    ret.push_back(i);
                }
                break;
        }
    }
    return ret;
}

std::ostream &operator<<(std::ostream &os, const vulkan::PhysicalDevice &that) {
    os << "Physical device: " << that.properties.deviceName;
    return os;
}

