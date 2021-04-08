//
// Created by jpc on 3/04/21.
//

#include <iostream>
#include <vulkan/vulkan.h>
#include "MainWindow.h"
#include "VulkanDevice.h"
#include "VulkanInstance.h"
#include "VulkanSwapchain.h"

MainWindow::MainWindow(const std::string& applicationName, int width, int height): vulkanInstance(applicationName) {
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);  // prevent auto opengl context creation
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);  // prevent resizing
    window = glfwCreateWindow(width, height, applicationName.c_str(), nullptr, nullptr);
    auto physicalDevices = vulkanInstance.getPhysicalDevices();
    if (physicalDevices.empty()){
        throw std::runtime_error("No physical devices found");
    }
    VulkanPhysicalDevice & physicalDevice = physicalDevices[0];  // choose a better strategy
    VulkanDevice logicalDevice(physicalDevice);
    if (glfwCreateWindowSurface(vulkanInstance.getInstance(), window, nullptr, &surface) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create window surface");
    }
    VulkanSwapchain swapchain(logicalDevice, surface);
#ifndef NDEBUG
    std::cout << "Main window created" << std::endl;
#endif
}

MainWindow::~MainWindow() {
    vkDestroySurfaceKHR(vulkanInstance.getInstance(), surface, nullptr);
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

