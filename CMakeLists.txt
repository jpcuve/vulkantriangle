cmake_minimum_required(VERSION 3.17)
project(vulkantest)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp macros.h MainWindow.cpp MainWindow.h vulkan/Instance.cpp vulkan/Instance.h vulkan/PhysicalDevice.cpp vulkan/PhysicalDevice.h Surface.cpp Surface.h vulkan/PhysicalDeviceList.cpp vulkan/PhysicalDeviceList.h)

find_package(Vulkan REQUIRED)
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES} Vulkan::Vulkan)