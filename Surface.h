//
// Created by jpc on 21/06/21.
//

#ifndef VULKANTEST_SURFACE_H
#define VULKANTEST_SURFACE_H


#include <vulkan/vulkan_core.h>
#include <GLFW/glfw3.h>
#include "vulkan/Instance.h"

class Surface {
private:
    VkSurfaceKHR handle {VK_NULL_HANDLE};
    VkInstance instanceHandle {VK_NULL_HANDLE};
public:
    Surface()= default;
    Surface(GLFWwindow *window, vulkan::Instance &instance);
    Surface(Surface& that) = delete;
    Surface &operator=(Surface &that) = delete;
    Surface &operator=(Surface &&that);
    ~Surface();
    VkSurfaceKHR get_handle(){ return handle; }
    friend std::ostream &operator<<(std::ostream &os, Surface &that);
};


#endif //VULKANTEST_SURFACE_H
