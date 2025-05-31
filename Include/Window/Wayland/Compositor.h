#ifndef STORMSINGER_WAYLAND_COMPOSITOR_H
#define STORMSINGER_WAYLAND_COMPOSITOR_H

#include <wayland-client.h>

void stormsinger_waylandBindCompositor(struct wl_registry *registry,
                                       uint32_t name);
void stormsinger_waylandCreateWindow(struct wl_display *display);
void stormsinger_waylandDestroyWindow();

struct wl_surface *stormsinger_waylandGetSurface(void);

#endif // STORMSINGER_WAYLAND_COMPOSITOR_H
