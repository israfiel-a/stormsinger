#ifndef STORMSINGER_WINDOW_WAYLAND_H
#define STORMSINGER_WINDOW_WAYLAND_H

#include <wayland-client.h>

bool stormsinger_waylandConnect(void);

struct wl_display *stormsinger_waylandGetDisplay(void);

bool stormsinger_waylandPollEvents(void);

uint32_t stormsinger_waylandGetWidth(void);
uint32_t stormsinger_waylandGetHeight(void);

#endif // STORMSINGER_WINDOW_WAYLAND_H
