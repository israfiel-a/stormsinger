#include <Vulkan/Surface.h>

#ifdef STORMSINGER_WAYLAND
#include <Vulkan/Surface/Wayland.h>
#endif

static VkSurfaceKHR pSurface = nullptr;

bool stormsinger_vulkanCreateSurface(VkInstance instance)
{
#ifdef STORMSINGER_WAYLAND
    pSurface = stormsinger_vulkanCreateWaylandSurface(instance);
    if (pSurface == nullptr) return false;
#endif

    return true;
}
