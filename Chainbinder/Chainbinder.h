#ifndef CHAINBINDER_ROOT_H
#define CHAINBINDER_ROOT_H

#include <stdbool.h>

typedef enum chainbinder_error
{
    CHAINBINDER_NO_ERROR
} chainbinder_error_t;

bool Chainbinder_Initialize(int argc, char **argv);
void Chainbinder_CleanUp(void);

void Chainbinder_Run(void);

chainbinder_error_t Chainbinder_GetError(void);

#endif // CHAINBINDER_ROOT_H
