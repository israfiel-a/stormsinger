#ifndef LIGHTBLEEDER_WINDOW_HPP
#define LIGHTBLEEDER_WINDOW_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string_view>

namespace Lightbleeder
{
    class Window
    {
        private:
            GLFWwindow *window;

        public:
            Window(std::string_view title);
    };
}

#endif // LIGHTBLEEDER_WINDOW_HPP
