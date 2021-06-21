//
// Created by jpc on 21/06/21.
//

#ifndef VULKANTEST_MAINWINDOW_H
#define VULKANTEST_MAINWINDOW_H

#include <iostream>
#include <memory>
#include <GLFW/glfw3.h>
#include "vulkan/Instance.h"


class MainWindow {
private:
    GLFWwindow *window;
    std::unique_ptr<vulkan::Instance> instance;

public:
    MainWindow(const char *title, const int width, const int height);
    MainWindow(MainWindow &that) = delete;
    MainWindow &operator=(MainWindow &that) = delete;
    MainWindow(MainWindow &&that) noexcept ;
    MainWindow &operator=(MainWindow &&that) noexcept ;
    ~MainWindow();
    void loop();
};


#endif //VULKANTEST_MAINWINDOW_H
