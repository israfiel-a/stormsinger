#include <Windowing/Wayland.h>
#include <stdio.h>
#include <wayland-client.h>

#include <Windowing/Wayland/Compositor.h>
#include <Windowing/Wayland/Registry.h>

static struct wl_display *pDisplay = nullptr;

bool stormsinger_waylandConnect(void)
{
    // TODO: Implment user-controlled Wayland server via command line
    // TODO: arguments given to the executable.
    pDisplay = wl_display_connect(nullptr);
    if (pDisplay == nullptr)
    {
        perror("Failed to connect to Wayland display server. Code: ");
        return false;
    }
    stormsinger_waylandConnectRegistry(pDisplay);
    stormsinger_waylandCreateWindow(pDisplay);

    return true;
}
