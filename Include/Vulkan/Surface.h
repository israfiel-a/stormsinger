#ifndef STORMSINGER_VULKAN_SURFACE_H
#define STORMSINGER_VULKAN_SURFACE_H

#include <vulkan/vulkan.h>

bool stormsinger_vulkanCreateSurface(VkInstance instance);

VkSurfaceCapabilitiesKHR
stormsinger_vulkanFindSurfaceCapabilities(VkPhysicalDevice device);

VkSurfaceCapabilitiesKHR stormsinger_vulkanGetSurfaceCapabilities();

VkExtent2D stormsinger_vulkanGetSurfaceExtent(void);

VkSurfaceFormatKHR *
stormsinger_vulkanGetSurfaceFormats(VkPhysicalDevice device);

VkPresentModeKHR *
stormsinger_vulkanGetSurfaceModes(VkPhysicalDevice device);

VkSurfaceFormatKHR stormsinger_vulkanChooseSurfaceFormat(void);
VkPresentModeKHR stormsinger_vulkanChooseSurfaceMode(void);

VkSurfaceKHR stormsinger_vulkanGetSurface(void);

#endif // STORMSINGER_VULKAN_SURFACE_H
