#ifndef LIGHTBLEEDER_WINDOW_HPP
#define LIGHTBLEEDER_WINDOW_HPP

#include <GLFW/glfw3.h>

#include <string_view>

namespace Lightbleeder
{
    class Window
    {
        private:
            GLFWwindow *window;
            Window();

        public:
            inline static Window &Get()
            {
                static Window instance;
                return instance;
            }

            inline void
            SetTitle(const std::string_view title) const noexcept
            {
                glfwSetWindowTitle(window, title.data());
            }

            // We don't want to allow copying or moving the window's data
            // in any way.
            Window(Window const &) = delete;
            void operator=(const Window &) = delete;
    };
}

#endif // LIGHTBLEEDER_WINDOW_HPP
