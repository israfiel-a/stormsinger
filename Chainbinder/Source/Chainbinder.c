#include <Chainbinder.h>
#include <Window.h>
#include <stdio.h>

void Chainbinder_Initialize(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    _Chainbinder_CreateWindow();
}

void Chainbinder_CleanUp(void) { _Chainbinder_DestroyWindow(); }

void Chainbinder_Run(void) {}

// TODO: Not yet implemented.
chainbinder_error_t Chainbinder_GetError(void)
{
    return CHAINBINDER_NO_ERROR;
}
