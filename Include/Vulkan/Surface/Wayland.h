#ifndef STORMSINGER_SURFACE_WAYLAND_H
#define STORMSINGER_SURFACE_WAYLAND_H

#include <vulkan/vulkan.h>
#include <wayland-client.h>

VkSurfaceKHR stormsinger_vulkanCreateWaylandSurface(VkInstance instance);

#endif // STORMSINGER_SURFACE_WAYLAND_H
