//
// Created by jpc on 3/04/21.
//

#ifndef VULKANTEST_MAINWINDOW_H
#define VULKANTEST_MAINWINDOW_H


#include <GLFW/glfw3.h>
#include "VulkanInstance.h"

class MainWindow {
private:
    GLFWwindow* window;
    VulkanInstance vulkanInstance;
    VkSurfaceKHR surface{};
public:
    MainWindow(const std::string& applicationName, int width, int height);
    ~MainWindow();
    void loop();
};


#endif //VULKANTEST_MAINWINDOW_H
