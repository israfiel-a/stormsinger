#include <Chainbinder.h>
#include <stdio.h>

void Chainbinder_Initialize(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("Hello, world!");
}

void Chainbinder_CleanUp(void) {}

void Chainbinder_Run(void) {}

// TODO: Not yet implemented.
chainbinder_error_t Chainbinder_GetError(void)
{
    return CHAINBINDER_NO_ERROR;
}
