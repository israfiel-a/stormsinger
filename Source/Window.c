#include <Window.h>

#ifdef STORMSINGER_WAYLAND
#include <Window/Wayland.h>
#endif

static bool pClose = false;

bool stormsinger_windowCreate(void)
{
#ifdef STORMSINGER_WAYLAND
    if (!stormsinger_waylandConnect()) return false;
#endif

    return true;
}

void stormsinger_windowClose(bool close) { pClose = close; }

void stormsinger_windowRun(void)
{
    while (!pClose)
    {
#ifdef STORMSINGER_WAYLAND
        if (!stormsinger_waylandPollEvents()) break;
#endif
    }
}

uint32_t stormsinger_windowGetWidth(void)
{
#ifdef STORMSINGER_WAYLAND
    return stormsinger_waylandGetWidth();
#endif
}

uint32_t stormsinger_windowGetHeight(void)
{
#ifdef STORMSINGER_WAYLAND
    return stormsinger_waylandGetHeight();
#endif
}
