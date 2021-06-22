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

Surface &Surface::operator=(Surface &&that) {
    handle = that.handle;
    that.handle = VK_NULL_HANDLE;
    instanceHandle = that.instanceHandle;
    that.instanceHandle = VK_NULL_HANDLE;
    return *this;
}

Surface::~Surface() {
    if (handle != VK_NULL_HANDLE && instanceHandle != VK_NULL_HANDLE){
        vkDestroySurfaceKHR(instanceHandle, handle, nullptr);
#ifndef NDEBUG
        std::cout << "surface destroyed" << std::endl;
#endif
    }
}

std::ostream &operator<<(std::ostream &os, Surface &that) {
    os << "Surface: " << that.handle;
    return os;
}

