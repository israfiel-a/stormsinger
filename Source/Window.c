#include <Window.h>

#ifdef STORMSINGER_WAYLAND
#include <Window/Wayland.h>
#endif

static bool pClose = false;

bool stormsinger_createWindow(void)
{
#ifdef STORMSINGER_WAYLAND
    if (!stormsinger_waylandConnect()) return false;
#endif

    return true;
}

void stormsinger_windowClose(bool close) { pClose = close; }

void stormsinger_runWindow(void)
{
    while (!pClose)
    {
#ifdef STORMSINGER_WAYLAND
        if (!stormsinger_waylandPollEvents()) break;
#endif
    }
}
