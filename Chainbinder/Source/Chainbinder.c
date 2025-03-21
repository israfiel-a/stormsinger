#include <Chainbinder.h>
#include <Vulkan/Context.h>
#include <Window.h>
#include <stdio.h>

bool Chainbinder_Initialize(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    if (!Chainbinder_CreateWindow("TEST", CHAINBINDER_SPLASHSCREEN))
        return false;
    // I would like to do this before creating the window, but GLFW
    // requires some extensions and in order to grab them, we need to have
    // the library initialized.
    if (!Chainbinder_CreateVulkanInstance()) return false;

    return true;
}

void Chainbinder_CleanUp(void)
{
    Chainbinder_DestroyWindow();
    Chainbinder_CleanupWindows();
    Chainbinder_DestroyVulkanInstance();
}

void Chainbinder_Run(void) { Chainbinder_RunWindow(); }

// TODO: Not yet implemented.
chainbinder_error_t Chainbinder_GetError(void)
{
    return CHAINBINDER_NO_ERROR;
}
