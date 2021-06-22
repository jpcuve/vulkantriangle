//
// Created by jpc on 21/06/21.
//

#include <memory>
#include <vector>
#include "MainWindow.h"
#include "Surface.h"

MainWindow::MainWindow(const char *title, int width, int height): handle {nullptr}, instance {nullptr} {
    handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
    uint32_t glfwExtensionCount = 0;
    const char **glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    std::vector<const char *> extensionNames {glfwExtensionCount};
    extensionNames.assign(glfwExtensions, glfwExtensions + glfwExtensionCount);
    instance = std::make_unique<vulkan::Instance>(extensionNames);
    surface = Surface(handle, *instance);
    std::cout << surface << std::endl;
}

MainWindow::~MainWindow() {
    if (handle){
        glfwDestroyWindow(handle);
    }
}

MainWindow::MainWindow(MainWindow &&that) noexcept {
    handle = that.handle;
    that.handle = nullptr;
}

MainWindow &MainWindow::operator=(MainWindow &&that) noexcept {
    handle = that.handle;
    that.handle = nullptr;
    return *this;
}

void MainWindow::loop() {
    while (!glfwWindowShouldClose(handle)) {
        glfwPollEvents();
    }
}
