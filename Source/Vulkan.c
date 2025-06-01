#include <Vulkan.h>
#include <Vulkan/Device.h>
#include <Vulkan/Surface.h>
#include <stdio.h>
#include <vulkan/vulkan.h>

static VkInstance pInstance = nullptr;

bool stormsinger_vulkanInitialize(void)
{
    VkApplicationInfo applicationInfo = {0};
    applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    applicationInfo.pApplicationName = "Stormsinger";
    applicationInfo.applicationVersion = STORMSINGER_VERSION;
    applicationInfo.pEngineName = nullptr;
    applicationInfo.engineVersion = 0;
    applicationInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo instanceInfo = {0};
    instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceInfo.pApplicationInfo = &applicationInfo;

    const char *extensions[2] = {"VK_KHR_surface",
#ifdef STORMSINGER_WAYLAND
                                 "VK_KHR_wayland_surface"
#endif
    };
    instanceInfo.enabledExtensionCount = 2;
    instanceInfo.ppEnabledExtensionNames = extensions;

    const char *layers[1] = {"VK_LAYER_KHRONOS_validation"};
    instanceInfo.enabledLayerCount = 1;
    instanceInfo.ppEnabledLayerNames = layers;

    VkResult result = vkCreateInstance(&instanceInfo, nullptr, &pInstance);
    if (result != VK_SUCCESS)
    {
        fprintf(stderr, "Failed to create Vulkan instance. Code: %d.\n",
                result);
        return false;
    }

    if (!stormsinger_vulkanCreateSurface(pInstance)) return false;
    if (!stormsinger_vulkanCreateDevice(pInstance)) return false;

    return true;
}

VkInstance stormsinger_getVulkan(void) { return pInstance; }
