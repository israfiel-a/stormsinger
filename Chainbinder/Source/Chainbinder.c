#include <Chainbinder.h>
#include <Window.h>
#include <stdio.h>

void Chainbinder_Initialize(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    Chainbinder_CreateWindow("TEST", CHAINBINDER_SPLASHSCREEN);
}

void Chainbinder_CleanUp(void)
{
    Chainbinder_DestroyWindow();
    Chainbinder_CleanupWindows();
}

void Chainbinder_Run(void) { Chainbinder_RunWindow(); }

// TODO: Not yet implemented.
chainbinder_error_t Chainbinder_GetError(void)
{
    return CHAINBINDER_NO_ERROR;
}
