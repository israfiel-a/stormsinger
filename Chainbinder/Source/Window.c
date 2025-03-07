#include <Logging.h>
#include <Window.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

static GLFWwindow *window_handle = CHAINBINDER_NULLPTR;

static void ErrorCallback(int code, const char *description)
{
    _Chainbinder_Log(CHAINBINDER_ERROR,
                     "Got GLFW error %d. Description: %s", code,
                     description);
}

bool _Chainbinder_CreateWindow(const char *const title)
{
    glfwSetErrorCallback(ErrorCallback);
    if (!glfwInit())
    {
        _Chainbinder_LogString(CHAINBINDER_ERROR,
                               "Failed to initialize GLFW.");
        return false;
    }

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    GLFWmonitor *primary_monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *primary_resolution =
        glfwGetVideoMode(primary_monitor);

    const int width = primary_resolution->width >> 1;
    const int height = primary_resolution->height >> 1;

    const int x = (primary_resolution->width >> 1) - (width >> 1);
    const int y = (primary_resolution->height >> 1) - (height >> 1);
    glfwWindowHint(GLFW_POSITION_X, x);
    glfwWindowHint(GLFW_POSITION_X, y);

    // While the application loads, we display a little window that tells
    // what the application is doing. We want this to be neither decorated
    // nor resizable.
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window_handle = glfwCreateWindow(
        width, height, title, CHAINBINDER_NULLPTR, CHAINBINDER_NULLPTR);
    if (window_handle == CHAINBINDER_NULLPTR)
    {
        _Chainbinder_LogString(CHAINBINDER_ERROR,
                               "Failed to create GLFW window.");
        return false;
    }

    return true;
}

void _Chainbinder_DestroyWindow(void)
{
    glfwDestroyWindow(window_handle);
    glfwTerminate();
}
