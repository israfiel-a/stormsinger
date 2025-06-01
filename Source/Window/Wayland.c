#include <Window/Wayland.h>
#include <stdio.h>
#include <wayland-client.h>

#include <Window/Wayland/Compositor.h>
#include <Window/Wayland/Registry.h>

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

struct wl_display *stormsinger_waylandGetDisplay(void) { return pDisplay; }

bool stormsinger_waylandPollEvents(void)
{
    return wl_display_dispatch(pDisplay) != -1;
}
