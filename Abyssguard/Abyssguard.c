#include <Chainbinder.h>

static void RunSunbringer(void)
{
    if (!Chainbinder_Execute("./Sunbringer.exe")) return;
}

int main(int argc, char **argv)
{
    RunSunbringer();

    if (!Chainbinder_Initialize(argc, argv)) return 1;
    // if (Chainbinder_GetError() != CHAINBINDER_NO_ERROR) return 1;

    Chainbinder_Run();

    Chainbinder_CleanUp();
    return 0;
}
