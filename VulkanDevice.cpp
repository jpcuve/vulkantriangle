//
// Created by jpc on 4/04/21.
//

#include "VulkanDevice.h"
#include <stdexcept>
#include <iostream>

const char* deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

VulkanDevice::VulkanDevice(VulkanPhysicalDevice & device): physicalDevice(device) {
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    float queuePriority = 1.0f;
    std::set<uint32_t> queueFamilyIndices = physicalDevice.getQueueIndices(VK_QUEUE_GRAPHICS_BIT);
    if (queueFamilyIndices.empty()){
        throw std::runtime_error("No graphics queue family indices");
    }
    for (uint32_t queueFamilyIndex: queueFamilyIndices) {
        VkDeviceQueueCreateInfo queueCreateInfo{
                .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
                .queueFamilyIndex = queueFamilyIndex,
                .queueCount = 1,
                .pQueuePriorities = &queuePriority,
        };
        queueCreateInfos.push_back(queueCreateInfo);
    }
    VkPhysicalDeviceFeatures deviceFeatures{};
    VkDeviceCreateInfo createInfo{
            .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
            .pNext = nullptr,
            .queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size()),
            .pQueueCreateInfos = queueCreateInfos.data(),
            .enabledLayerCount = 0, // TODO change
            .enabledExtensionCount = sizeof(*deviceExtensions),
            .ppEnabledExtensionNames = &deviceExtensions,
            .pEnabledFeatures = &deviceFeatures,
    };
    if (vkCreateDevice(physicalDevice.getDevice(), &createInfo, nullptr, &logicalDevice) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create logical device");
    }
#ifndef NDEBUG
    std::cout << "Vulkan device created" << std::endl;
#endif
}

VulkanDevice::~VulkanDevice() {
    vkDestroyDevice(logicalDevice, nullptr);
#ifndef NDEBUG
    std::cout << "Vulkan device destroyed" << std::endl;
#endif
}
