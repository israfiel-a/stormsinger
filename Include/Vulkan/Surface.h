#ifndef STORMSINGER_VULKAN_SURFACE_H
#define STORMSINGER_VULKAN_SURFACE_H

#include <vulkan/vulkan.h>

bool stormsinger_vulkanCreateSurface(VkInstance instance);

VkSurfaceKHR stormsinger_vulkanGetSurface(void);

#endif // STORMSINGER_VULKAN_SURFACE_H
