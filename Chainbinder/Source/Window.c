/**
 * @file Window.c
 * @author Israfiel Argos (israfiel-a)
 * @brief This file provides the implementation of the surface-level
 * abstraction Chainbinder creates over GLFW.
 *
 * @since 0.1.0
 * @updated 0.1.1
 *
 * @copyright (c) 2024-2025 - Israfil Argos
 * This document is under the GNU Affero General Public License v3.0. It
 * can be modified and distributed (commercially or otherwise) freely, and
 * can be used privately and within patents. No liability or warranty is
 * guaranteed. However, on use, the user must state license and copyright,
 * any changes made, and disclose the source of the document. For more
 * information see the @file LICENSE.md file included with this
 * distribution of the source code, or https://www.gnu.org/licenses/agpl.
 */

#include <Reporting.h>
#include <Window.h>

#define GLFW_INCLUDE_NONE // I prefer explicit includes.
#include <GLFW/glfw3.h>

/**
 * @brief The handle of the currently created window object.
 *
 * @since 0.1.0
 * @updated 0.1.1
 */
static GLFWwindow *window_handle = CHAINBINDER_NULLPTR;

/**
 * @brief The type of window currently created.
 *
 * @since 0.1.0
 * @updated 0.1.1
 */
static chainbinder_window_type_t window_type = 0;

/**
 * @brief A boolean representing whether or not GLFW has been initialized.
 *
 * @since 0.1.0
 * @updated 0.1.1
 */
static bool glfw_initialized = false;

/**
 * @brief The callback to be triggered whenever GLFW runs into an error.
 *
 * @since 0.1.0
 * @updated 0.1.1
 *
 * @param code The error code reported.
 * @param description A short, human-readable description of the error.
 */
CHAINBINDER_NONNULL(2) static void ErrorCallback(int code,
                                                 const char *description)
{
    Chainbinder_Log(CHAINBINDER_ERROR,
                    "Got GLFW error %d. Description: %s", code,
                    description);

#if STORMSINGER_DISABLE_LOGS
    // The above log will expand to nothing in this scenario, so we have to
    // reference the parameters to prevent an MSVC tantrum.
    (void)code;
    (void)description;
#endif
}

/**
 * @brief Initialize the GLFW library.
 *
 * @since 0.1.1
 * @updated 0.1.1
 *
 * @returns A boolean flag representing the success of the operation.
 */
CHAINBINDER_NOIGNORE static inline bool InitializeGLFW(void)
{
    if (glfw_initialized)
    {
        Chainbinder_Log(CHAINBINDER_WARNING,
                        "Tried to initialize GLFW twice.");
        return true;
    }

    glfwSetErrorCallback(ErrorCallback);

    // I HATE libdecor's decorations--and we don't need it, anyway. None of
    // the created windows are decorated.
    glfwInitHint(GLFW_WAYLAND_LIBDECOR, GLFW_WAYLAND_DISABLE_LIBDECOR);
    if (!glfwInit())
    {
        Chainbinder_Log(CHAINBINDER_ERROR, "Failed to initialize GLFW.");
        return false;
    }
    Chainbinder_Log(CHAINBINDER_SUCCESS, "Initialized GLFW.");
    glfw_initialized = true;
    return true;
}

/**
 * @brief Set the window hints for the set window type, and get the desired
 * dimensions for said window type.
 *
 * @since 0.1.1
 * @updated 0.1.1
 *
 * @param resolution The information about the monitor we're currently on.
 * @param width A place to store the desired width for the window.
 * @param height A place to store the desired height for the window.
 */
CHAINBINDER_NONNULL(1, 2, 3) static inline void
SetHints(const GLFWvidmode *resolution, const char *const title,
         int *width, int *height)
{
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

    if (window_type == CHAINBINDER_SPLASHSCREEN)
    {
        *width = resolution->width >> 2;
        *height = resolution->height >> 2;

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

    glfwWindowHintString(GLFW_WAYLAND_APP_ID, title);
    glfwWindowHintString(GLFW_X11_CLASS_NAME, title);
    glfwWindowHintString(GLFW_X11_INSTANCE_NAME, title);
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
    SetHints(primary_resolution, title, &width, &height);

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
    if (window_handle == CHAINBINDER_NULLPTR)
    {
        Chainbinder_Log(CHAINBINDER_WARNING,
                        "Tried to destroy window before its creation.");
        return;
    }

    glfwDestroyWindow(window_handle);
    Chainbinder_Log(CHAINBINDER_NOTICE, "Destroyed window of type %d.",
                    window_type);

    window_handle = CHAINBINDER_NULLPTR;
    window_type = 0;
}

void Chainbinder_RunWindow(void)
{
    if (window_handle == CHAINBINDER_NULLPTR)
    {
        Chainbinder_Log(CHAINBINDER_WARNING,
                        "Tried to run window before its creation.");
        return;
    }

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
