#include "Window.hpp"

#include <iostream>
#include <stdexcept>

namespace Lightbleeder
{
    Window::Window(std::string_view title)
    {
        bool initialized = (bool)glfwInit();
        if (!initialized)
            // TODO: Log system.
            throw std::runtime_error("Failed to initialize GLFW.");

        glfwDefaultWindowHints();
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        GLFWmonitor *monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode *mode = glfwGetVideoMode(monitor);

        window = glfwCreateWindow(mode->width, mode->height, title.data(),
                                  monitor, nullptr);
        if (window == nullptr)
            throw std::runtime_error("Failed to create window.");

        while (!glfwWindowShouldClose(window)) { glfwPollEvents(); }
    }
}
