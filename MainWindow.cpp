//
// Created by jpc on 3/04/21.
//

#include <iostream>
#include <vulkan/vulkan.h>
#include "MainWindow.h"
#include "VulkanDevice.h"
#include "VulkanInstance.h"
#include "VulkanSwapchain.h"
#include "macros.h"

const char* deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

MainWindow::MainWindow(const std::string& applicationName, int width, int height): vulkanInstance(applicationName) {
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);  // prevent auto opengl context creation
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);  // prevent resizing
    window = glfwCreateWindow(width, height, applicationName.c_str(), nullptr, nullptr);
    auto physicalDevices = vulkanInstance.getPhysicalDevices();
    if (physicalDevices.empty()){
        throw std::runtime_error("No physical devices found");
    }
    VulkanPhysicalDevice & physicalDevice = physicalDevices[0];  // choose a better strategy
    if (physicalDevice.getQueueFamilies().empty()){
        throw std::runtime_error("No graphics queue family indices");
    }
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    float queuePriority = 1.0f;
    for (auto & queueFamily: physicalDevice.getQueueFamilies()){
        if (queueFamily.isGraphics()){
            VkDeviceQueueCreateInfo queueCreateInfo{
                    .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
                    .queueFamilyIndex = queueFamily.getIndex(),
                    .queueCount = 1,
                    .pQueuePriorities = &queuePriority,
            };
            queueCreateInfos.push_back(queueCreateInfo);
        }
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
    if (vkCreateDevice(physicalDevice.getDevice(), &createInfo, nullptr, &device) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create logical device");
    }
    if (glfwCreateWindowSurface(vulkanInstance.getInstance(), window, nullptr, &surface) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create window surface");
    }
    // VulkanSwapchain swapchain(device, surface);
    DEBUG("Main window created");
}

MainWindow::~MainWindow() {
    vkDestroySurfaceKHR(vulkanInstance.getInstance(), surface, nullptr);
    vkDestroyDevice(device, nullptr);
    glfwDestroyWindow(window);
#ifndef NDEBUG
    std::cout << "Main window destroyed" << std::endl;
#endif
}

void MainWindow::loop() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}

