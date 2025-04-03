#include <Chainbinder.h>
#include <Reporting.h>

static void RunSunbringer(void)
{
    if (!Chainbinder_Execute("./Sunbringer.exe"))
    {
        Chainbinder_Log(CHAINBINDER_NOTICE,
                        "Unable to properly run Sunbringer.");
        return;
    }
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
