#include <Window.h>
#include <Window/Wayland/Compositor.h>
#include <Window/Wayland/Output.h>
#include <Window/Wayland/Shell.h>
#include <stdio.h>
#include <wayland-client.h>

static struct wl_compositor *pCompositor = nullptr;
static struct wl_surface *pSurface = nullptr;
static struct xdg_surface *pShellSurface = nullptr;
static struct xdg_toplevel *pToplevel = nullptr;

static uint32_t pWidth = 0;
static uint32_t pHeight = 0;

static void handleConfigure(void *data, struct xdg_surface *shellSurface,
                            uint32_t serial)
{
    (void)data;
    xdg_surface_ack_configure(shellSurface, serial);
}

static const struct xdg_surface_listener pSurfaceListener = {
    .configure = handleConfigure};

static void handleTopClose(void *data, struct xdg_toplevel *toplevel)
{
    (void)data;
    (void)toplevel;
    stormsinger_windowClose(true);
}

static void handleTopConfigure(void *data, struct xdg_toplevel *toplevel,
                               int32_t width, int32_t height,
                               struct wl_array *states)
{
    (void)data;
    (void)toplevel;
    (void)states;

    pWidth = width;
    pHeight = height;
    printf("Window dimensions adjusted: %dx%d.\n", width, height);
}

static void handleTopConfigureBounds(void *data,
                                     struct xdg_toplevel *toplevel,
                                     int32_t width, int32_t height)
{
    (void)data;
    (void)toplevel;
    (void)width;
    (void)height;
}

static void handleCapabilities(void *data, struct xdg_toplevel *toplevel,
                               struct wl_array *capabilities)
{
    (void)data;
    (void)toplevel;
    (void)capabilities;
}

static const struct xdg_toplevel_listener pToplevelListener = {
    .close = handleTopClose,
    .configure = handleTopConfigure,
    .configure_bounds = handleTopConfigureBounds,
    .wm_capabilities = handleCapabilities};

void stormsinger_waylandBindCompositor(struct wl_registry *registry,
                                       uint32_t name)
{
    pCompositor =
        wl_registry_bind(registry, name, &wl_compositor_interface, 1);
    if (pCompositor == nullptr)
        perror("Failed to connect to compositor. Code: ");
}

void stormsinger_waylandCreateWindow(struct wl_display *display)
{
    pSurface = wl_compositor_create_surface(pCompositor);
    pShellSurface = xdg_wm_base_get_xdg_surface(
        stormsinger_waylandGetShell(), pSurface);
    xdg_surface_add_listener(pShellSurface, &pSurfaceListener, nullptr);

    pToplevel = xdg_surface_get_toplevel(pShellSurface);
    xdg_toplevel_add_listener(pToplevel, &pToplevelListener, nullptr);

    xdg_toplevel_set_title(pToplevel, "Stormsinger");
    xdg_toplevel_set_app_id(pToplevel, "Stormsinger");
    xdg_toplevel_set_fullscreen(pToplevel, stormsinger_waylandGetOutput());

    wl_surface_commit(pSurface);
    wl_display_roundtrip(display);
    wl_surface_commit(pSurface);
}

void stormsinger_waylandDestroyWindow() {}

struct wl_surface *stormsinger_waylandGetSurface(void) { return pSurface; }

uint32_t stormsinger_waylandGetSurfaceWidth(void) { return pWidth; }
uint32_t stormsinger_waylandGetSurfaceHeight(void) { return pHeight; }
