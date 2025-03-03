#include <Chainbinder.h>

int main(int argc, char **argv)
{
    Chainbinder_Initialize(argc, argv);
    if (Chainbinder_GetError() != CHAINBINDER_NO_ERROR) return 1;

    Chainbinder_Run();

    Chainbinder_CleanUp();
    return 0;
}
