#include <Logging.h>
#include <Window.h>

bool _Chainbinder_CreateWindow(void)
{
    _Chainbinder_LogString(CHAINBINDER_VERBOSE, "loglogolgo");
    _Chainbinder_LogString(CHAINBINDER_LOG, "loglogolgo");
    _Chainbinder_LogString(CHAINBINDER_SUCCESS, "loglogolgo");
    _Chainbinder_LogString(CHAINBINDER_NOTICE, "loglogolgo");
    _Chainbinder_LogString(CHAINBINDER_WARNING, "loglogolgo");
    _Chainbinder_LogString(CHAINBINDER_ERROR, "loglogolgo");
    return true;
}

void _Chainbinder_DestroyWindow(void) {}
