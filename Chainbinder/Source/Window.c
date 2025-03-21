#include <Reporting.h>
#include <Window.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

static GLFWwindow *window_handle = CHAINBINDER_NULLPTR;
static chainbinder_window_type_t window_type = 0;
static bool glfw_initialized = false;

static void ErrorCallback(int code, const char *description)
{
    Chainbinder_Log(CHAINBINDER_ERROR,
                    "Got GLFW error %d. Description: %s", code,
                    description);
}

static inline bool InitializeGLFW(void)
{
    if (glfw_initialized) return true;

    glfwSetErrorCallback(ErrorCallback);
    if (!glfwInit())
    {
        Chainbinder_Log(CHAINBINDER_ERROR, "Failed to initialize GLFW.");
        return false;
    }
    Chainbinder_Log(CHAINBINDER_SUCCESS, "Initialized GLFW.");
    glfw_initialized = true;
    return true;
}

static inline void SetHints(const GLFWvidmode *resolution, int *width,
                            int *height)
{
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    if (window_type == CHAINBINDER_SPLASHSCREEN)
    {
        *width = resolution->width >> 2;
        *height = resolution->height >> 2;

        glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    }
    else
    {
        *width = resolution->width;
        *height = resolution->height;

        glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
    }
    Chainbinder_Log(CHAINBINDER_VERBOSE, "Set window hints.");

    const int x = (resolution->width >> 1) - (*width >> 1);
    const int y = (resolution->height >> 1) - (*height >> 1);

    glfwWindowHint(GLFW_POSITION_X, x);
    glfwWindowHint(GLFW_POSITION_Y, y);
    Chainbinder_Log(CHAINBINDER_VERBOSE, "Setup %dx%d window at (%d, %d).",
                    *width, *height, x, y);
}

bool Chainbinder_CreateWindow(const char *const title,
                              chainbinder_window_type_t type)
{
    if (window_handle != CHAINBINDER_NULLPTR)
    {
        Chainbinder_Log(CHAINBINDER_WARNING,
                        "Attempted to create two windows at once.");
        return false;
    }

    if (!InitializeGLFW()) return false;
    window_type = type;
    Chainbinder_Log(CHAINBINDER_NOTICE, "Creating window of type %d.",
                    window_type);

    GLFWmonitor *primary_monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *primary_resolution =
        glfwGetVideoMode(primary_monitor);
    Chainbinder_Log(CHAINBINDER_VERBOSE,
                    "Got monitor of dimensions %dx%d.",
                    primary_resolution->width, primary_resolution->height);

    int width, height;
    SetHints(primary_resolution, &width, &height);

    window_handle = glfwCreateWindow(
        width, height, title, CHAINBINDER_NULLPTR, CHAINBINDER_NULLPTR);
    if (window_handle == CHAINBINDER_NULLPTR)
    {
        Chainbinder_Log(CHAINBINDER_ERROR,
                        "Failed to create GLFW window.");
        return false;
    }
    Chainbinder_Log(CHAINBINDER_SUCCESS, "Created window with title '%s'.",
                    title);

    return true;
}

void Chainbinder_DestroyWindow(void)
{
    glfwDestroyWindow(window_handle);
    Chainbinder_Log(CHAINBINDER_NOTICE, "Destroyed window of type %d.",
                    window_type);

    window_handle = CHAINBINDER_NULLPTR;
    window_type = 0;
}

void Chainbinder_RunWindow(void)
{
    glfwShowWindow(window_handle);
    while (!glfwWindowShouldClose(window_handle)) glfwPollEvents();
}

void Chainbinder_CleanupWindows(void)
{
    glfwSetErrorCallback(CHAINBINDER_NULLPTR);
    glfwTerminate();
    glfw_initialized = false;
    Chainbinder_Log(CHAINBINDER_NOTICE, "Terminated GLFW.");
}
