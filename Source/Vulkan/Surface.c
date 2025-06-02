#include <Vulkan/Surface.h>
#include <Window.h>
#include <stdlib.h>

#ifdef STORMSINGER_WAYLAND
#include <Vulkan/Surface/Wayland.h>
#endif

static VkSurfaceKHR pSurface = nullptr;
static uint32_t pFormatCount = 0;
static VkSurfaceFormatKHR *pFormats = nullptr;
static uint32_t pModeCount = 0;
static VkPresentModeKHR *pModes = nullptr;

static VkSurfaceCapabilitiesKHR pCapabilities;
static VkSurfaceFormatKHR pFormat;
static VkPresentModeKHR pMode;

bool stormsinger_vulkanCreateSurface(VkInstance instance)
{
#ifdef STORMSINGER_WAYLAND
    pSurface = stormsinger_vulkanCreateWaylandSurface(instance);
    if (pSurface == nullptr) return false;
#endif

    return true;
}

VkSurfaceCapabilitiesKHR
stormsinger_vulkanGetSurfaceCapabilities(VkPhysicalDevice device)
{
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, pSurface,
                                              &pCapabilities);
    return pCapabilities;
}

// TODO: Get this the fuck outta here.
// https://stackoverflow.com/questions/427477/fastest-way-to-clamp-a-real-fixed-floating-point-value#16659263
uint32_t _clamp(uint32_t d, uint32_t min, uint32_t max)
{
    const uint32_t t = d < min ? min : d;
    return t > max ? max : t;
}

VkExtent2D stormsinger_vulkanGetSurfaceExtent(void)
{
    if (pCapabilities.currentExtent.width != UINT32_MAX)
        return pCapabilities.currentExtent;

    VkExtent2D surfaceExtent = {
        .width = stormsinger_windowGetFramebufferWidth(),
        .height = stormsinger_windowGetFramebufferHeight()};

    surfaceExtent.width =
        _clamp(surfaceExtent.width, pCapabilities.minImageExtent.width,
               pCapabilities.maxImageExtent.width);
    surfaceExtent.height =
        _clamp(surfaceExtent.height, pCapabilities.minImageExtent.height,
               pCapabilities.maxImageExtent.height);

    return surfaceExtent;
}

VkSurfaceFormatKHR *
stormsinger_vulkanGetSurfaceFormats(VkPhysicalDevice device)
{
    if (pFormats != nullptr) return pFormats;

    vkGetPhysicalDeviceSurfaceFormatsKHR(device, pSurface, &pFormatCount,
                                         nullptr);
    if (pFormatCount == 0) return nullptr;
    pFormats = malloc(sizeof(VkSurfaceFormatKHR) * pFormatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, pSurface, &pFormatCount,
                                         pFormats);
    return pFormats;
}

VkPresentModeKHR *
stormsinger_vulkanGetSurfaceModes(VkPhysicalDevice device)
{
    if (pModes != nullptr) return pModes;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, pSurface,
                                              &pModeCount, nullptr);
    if (pModeCount == 0) return nullptr;
    pModes = malloc(sizeof(VkPresentModeKHR) * pModeCount);
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, pSurface,
                                              &pModeCount, pModes);
    return pModes;
}

VkSurfaceFormatKHR stormsinger_vulkanChooseSurfaceFormat(void)
{
    for (size_t i = 0; i < pFormatCount; i++)
    {
        VkSurfaceFormatKHR format = pFormats[i];
        // This is the best combination. If not available, we'll just
        // select the first provided colorspace.
        if (format.format == VK_FORMAT_B8G8R8A8_SRGB &&
            format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
        {
            pFormat = format;
            return pFormat;
        }
    }
    return pFormats[0];
}
VkPresentModeKHR stormsinger_vulkanChooseSurfaceMode(void)
{
    for (size_t i = 0; i < pModeCount; i++)
    {
        // This is the best mode. If not available, we'll just select
        // VK_PRESENT_MODE_FIFO_KHR.
        if (pModes[i] == VK_PRESENT_MODE_MAILBOX_KHR)
        {
            pMode = pModes[i];
            return pMode;
        }
    }
    return VK_PRESENT_MODE_FIFO_KHR;
}

VkSurfaceKHR stormsinger_vulkanGetSurface(void) { return pSurface; }
