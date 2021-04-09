cmake_minimum_required(VERSION 3.17)
project(vulkantest)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp MainWindow.cpp MainWindow.h VulkanInstance.cpp VulkanInstance.h VulkanDevice.cpp VulkanDevice.h VulkanPhysicalDevice.cpp VulkanPhysicalDevice.h VulkanSwapchain.cpp VulkanSwapchain.h macros.h)

find_package(Vulkan REQUIRED)
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES} Vulkan::Vulkan)