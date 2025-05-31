#ifndef STORMSINGER_WAYLAND_SHELL_H
#define STORMSINGER_WAYLAND_SHELL_H

#include <wayland-client.h>
#include <xdg-shell-protocol.h>

void stormsinger_waylandBindShell(struct wl_registry *registry,
                                  uint32_t name);

struct xdg_wm_base *stormsinger_waylandGetShell(void);

#endif // STORMSINGER_WAYLAND_SHELL_H
