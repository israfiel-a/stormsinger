#ifndef STORMSINGER_VULKAN_DEVICE_H
#define STORMSINGER_VULKAN_DEVICE_H

#include <vulkan/vulkan.h>

bool stormsinger_vulkanCreateDevice(VkInstance instance);

uint32_t stormsinger_vulkanGetGraphicsIndex(void);
uint32_t stormsinger_vulkanGetPresentIndex(void);

#endif // STORMSINGER_VULKAN_DEVICE_H
