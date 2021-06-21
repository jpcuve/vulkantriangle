//
// Created by jpc on 21/06/21.
//

#include <iostream>
#include "Surface.h"

Surface::Surface(GLFWwindow *window, vulkan::Instance &instance): instanceHandle{instance.instance()} {
    if (glfwCreateWindowSurface(instanceHandle, window, nullptr, &handle) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create handle surface");
    }
#ifndef NDEBUG
    std::cout << "surface constructed" << std::endl;
#endif
}

Surface::~Surface() {
    if (handle != VK_NULL_HANDLE){
        vkDestroySurfaceKHR(instanceHandle, handle, nullptr);
#ifndef NDEBUG
        std::cout << "surface destroyed" << std::endl;
#endif
    }
}
