#include <Chainbinder.h>
#include <Reporting.h>
#include <Sunbringer.h>

static void RunSunbringer(void)
{
    if (Chainbinder_Execute("./" SUNBRINGER_FILENAME,
                            CHAINBINDER_NULLPTR) == -1)
    {
        Chainbinder_Log(CHAINBINDER_NOTICE,
                        "Unable to properly run Sunbringer.");
        return;
    }
    (void)Chainbinder_DeleteFile("./" SUNBRINGER_FILENAME);
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
