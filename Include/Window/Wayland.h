#ifndef STORMSINGER_WINDOW_WAYLAND_H
#define STORMSINGER_WINDOW_WAYLAND_H

#include <wayland-client.h>

bool stormsinger_waylandConnect(void);

struct wl_display *stormsinger_waylandGetDisplay(void);

#endif // STORMSINGER_WINDOW_WAYLAND_H
