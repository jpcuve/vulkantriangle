//
// Created by jpc on 21/06/21.
//

#include <memory>
#include <vector>
#include <chrono>
#include "MainWindow.h"
#include "Surface.h"

MainWindow::MainWindow(const char *title, int width, int height): handle {nullptr} {
    handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
    uint32_t glfwExtensionCount = 0;
    const char **glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    std::vector<const char *> extensionNames {glfwExtensionCount};
    extensionNames.assign(glfwExtensions, glfwExtensions + glfwExtensionCount);
    instance = vulkan::Instance {extensionNames};
    surface = Surface(handle, instance);
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
    glfwSwapInterval(1); // enable VSync, does not seem to work
#ifndef NDEBUG
    long frame_count = 0L;
    auto start = std::chrono::high_resolution_clock::now();
#endif
    while (!glfwWindowShouldClose(handle)) {
        glfwSwapBuffers(handle);
        glfwPollEvents();
#ifndef NDEBUG
        frame_count++;
        auto now = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);
        if (duration.count() > 1000){
            std::cout << "fps: " << frame_count << std::endl;
            frame_count = 0L;
            start = std::chrono::high_resolution_clock::now();
        }
#endif
    }
}
