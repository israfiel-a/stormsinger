#include <Vulkan/Surface/Wayland.h>
#include <Window/Wayland.h>
#include <Window/Wayland/Compositor.h>
#include <stdio.h>
#include <vulkan/vulkan_wayland.h>

VkSurfaceKHR stormsinger_vulkanCreateWaylandSurface(VkInstance instance)
{
    VkWaylandSurfaceCreateInfoKHR createInfo = {0};
    createInfo.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
    createInfo.display = stormsinger_waylandGetDisplay();
    createInfo.surface = stormsinger_waylandGetSurface();

    VkSurfaceKHR createdSurface;
    VkResult code = vkCreateWaylandSurfaceKHR(instance, &createInfo,
                                              nullptr, &createdSurface);
    if (code != VK_SUCCESS)
    {
        fprintf(
            stderr,
            "Failed to create Vulkan-Wayland interop surface. Code: %d.\n",
            code);
        return nullptr;
    }
    return createdSurface;
}
