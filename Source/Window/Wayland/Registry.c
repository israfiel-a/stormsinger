#include <Window/Wayland/Registry.h>
#include <string.h>
#include <xdg-shell-protocol.h>

#include <Window/Wayland/Compositor.h>
#include <Window/Wayland/Shell.h>

static struct wl_registry *pRegistry = nullptr;

static void handleGlobal(void *data, struct wl_registry *registry,
                         uint32_t name, const char *interface,
                         uint32_t version)
{
    (void)data;
    (void)version;

    if (strcmp(interface, wl_compositor_interface.name) == 0)
        stormsinger_waylandBindCompositor(registry, name);
    else if (strcmp(interface, xdg_wm_base_interface.name) == 0)
        stormsinger_waylandBindShell(registry, name);
}

static void handleGlobalRemove(void *data, struct wl_registry *registry,
                               uint32_t name)
{
    (void)data;
    (void)registry;
    (void)name;
}

static const struct wl_registry_listener pRegistryListener = {
    .global = handleGlobal, .global_remove = handleGlobalRemove};

void stormsinger_waylandConnectRegistry(struct wl_display *display)
{
    // This call ostensibly cannot fail if display is properly gotten.
    pRegistry = wl_display_get_registry(display);

    (void)wl_registry_add_listener(pRegistry, &pRegistryListener, nullptr);
    (void)wl_display_roundtrip(display);
}
