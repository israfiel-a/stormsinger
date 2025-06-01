#include <Window/Wayland/Output.h>
#include <stdio.h>

static struct wl_output *pOutput = nullptr;

void stormsinger_waylandBindOutput(struct wl_registry *registry,
                                   uint32_t name)
{
    pOutput = wl_registry_bind(registry, name, &wl_output_interface, 1);
    if (pOutput == nullptr) perror("Failed to connect to output. Code: ");
}

struct wl_output *stormsinger_waylandGetOutput(void) { return pOutput; }
