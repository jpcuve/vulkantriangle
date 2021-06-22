//
// Created by jpc on 21/06/21.
//

#ifndef VULKANTEST_MAINWINDOW_H
#define VULKANTEST_MAINWINDOW_H

#include <iostream>
#include <memory>
#include <GLFW/glfw3.h>
#include "vulkan/Instance.h"
#include "Surface.h"


class MainWindow {
private:
    GLFWwindow *handle {nullptr};
    std::unique_ptr<vulkan::Instance> instance;
    Surface surface;

public:
    MainWindow(const char *title, int width, int height);
    MainWindow(MainWindow &that) = delete;
    MainWindow &operator=(MainWindow &that) = delete;
    MainWindow(MainWindow &&that) noexcept ;
    MainWindow &operator=(MainWindow &&that) noexcept ;
    ~MainWindow();
    void loop();
};


#endif //VULKANTEST_MAINWINDOW_H
