#include <Window/Wayland/Output.h>
#include <stdio.h>

static struct wl_output *pOutput = nullptr;

static int32_t pScaleFactor = 0;

void handleGeometry(void *data, struct wl_output *output, int32_t x,
                    int32_t y, int32_t physical_width,
                    int32_t physical_height, int32_t subpixel,
                    const char *make, const char *model, int32_t transform)
{
    (void)data;
    (void)output;
    (void)x;
    (void)y;
    (void)physical_width;
    (void)physical_height;
    (void)subpixel;
    (void)make;
    (void)model;
    (void)transform;
}

void handleMode(void *data, struct wl_output *output, uint32_t flags,
                int32_t width, int32_t height, int32_t refresh)
{
    (void)data;
    (void)output;
    (void)flags;
    (void)width;
    (void)height;
    (void)refresh;
}

void handleFinish(void *data, struct wl_output *output)
{
    (void)data;
    (void)output;
}

void handleScale(void *data, struct wl_output *output, int32_t factor)
{
    (void)data;
    (void)output;
    pScaleFactor = factor;
    printf("Monitor scale %d.\n", pScaleFactor);
}

void handleName(void *data, struct wl_output *output, const char *name)
{
    (void)data;
    (void)output;
    (void)name;
}

void handleDescription(void *data, struct wl_output *output,
                       const char *description)
{
    (void)data;
    (void)output;
    (void)description;
}

static const struct wl_output_listener outputListener = {
    .description = handleDescription,
    .done = handleFinish,
    .geometry = handleGeometry,
    .mode = handleMode,
    .name = handleName,
    .scale = handleScale};

void stormsinger_waylandBindOutput(struct wl_registry *registry,
                                   uint32_t name)
{
    pOutput = wl_registry_bind(registry, name, &wl_output_interface, 2);
    if (pOutput == nullptr) perror("Failed to connect to output. Code: ");
    wl_output_add_listener(pOutput, &outputListener, nullptr);
}

struct wl_output *stormsinger_waylandGetOutput(void) { return pOutput; }

int32_t stormsinger_waylandGetOutputScale(void) { return pScaleFactor; }
