#include <Windowing.h>

#ifdef STORMSINGER_WAYLAND
#include <Windowing/Wayland.h>
#endif

bool stormsinger_createWindow(void)
{
#ifdef STORMSINGER_WAYLAND
    if (!stormsinger_waylandConnect()) return false;
#endif

    return true;
}
