#include <Windowing/Wayland/Shell.h>
#include <xdg-shell-protocol.h>

static struct xdg_wm_base *pShell = nullptr;

static void handlePing(void *data, struct xdg_wm_base *shell,
                       uint32_t serial)
{
    (void)data;
    xdg_wm_base_pong(shell, serial);
}

static struct xdg_wm_base_listener pShellListener = {.ping = handlePing};

void stormsinger_waylandBindShell(struct wl_registry *registry,
                                  uint32_t name)
{
    pShell = wl_registry_bind(registry, name, &xdg_wm_base_interface, 1);
    xdg_wm_base_add_listener(pShell, &pShellListener, NULL);
}

struct xdg_wm_base *stormsinger_waylandGetShell(void) { return pShell; }
