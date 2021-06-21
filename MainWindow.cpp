//
// Created by jpc on 21/06/21.
//

#include <vector>
#include <memory>
#include "MainWindow.h"

MainWindow::MainWindow(const char *title, const int width, const int height): window {nullptr}, instance {nullptr} {
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    uint32_t glfwExtensionCount = 0;
    const char **glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    std::vector<const char *> extensionNames {glfwExtensionCount};
    extensionNames.assign(glfwExtensions, glfwExtensions + glfwExtensionCount);
    instance = std::make_unique<vulkan::Instance>(extensionNames);
}

MainWindow::~MainWindow() {
    if (window){
        glfwDestroyWindow(window);
    }
}

MainWindow::MainWindow(MainWindow &&that) noexcept {
    window = that.window;
    that.window = nullptr;
}

MainWindow &MainWindow::operator=(MainWindow &&that) noexcept {
    window = that.window;
    that.window = nullptr;
    return *this;
}

void MainWindow::loop() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}
