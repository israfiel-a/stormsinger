#ifndef STORMSINGER_WAYLAND_OUTPUT_H
#define STORMSINGER_WAYLAND_OUTPUT_H

#include <wayland-client.h>

void stormsinger_waylandBindOutput(struct wl_registry *registry,
                                   uint32_t name);

struct wl_output *stormsinger_waylandGetOutput(void);

#endif // STORMSINGER_WAYLAND_OUTPUT_H
