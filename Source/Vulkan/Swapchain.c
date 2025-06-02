#include <Vulkan/Device.h>
#include <Vulkan/Surface.h>
#include <Vulkan/Swapchain.h>
#include <stdio.h>
#include <stdlib.h>
#include <vulkan/vulkan.h>

static VkSwapchainKHR pSwapchain = nullptr;
static VkImageView *pSwapchainImages = nullptr;

bool stormsinger_vulkanCreateSwapchain(VkDevice logicalDevice)
{
    VkSurfaceFormatKHR format = stormsinger_vulkanChooseSurfaceFormat();
    VkPresentModeKHR mode = stormsinger_vulkanChooseSurfaceMode();
    VkExtent2D extent = stormsinger_vulkanGetSurfaceExtent();
    VkSurfaceCapabilitiesKHR capabilities =
        stormsinger_vulkanGetSurfaceCapabilities();

    uint32_t imageCount = capabilities.minImageCount + 1;
    if (capabilities.maxImageCount > 0 &&
        imageCount > capabilities.maxImageCount)
        imageCount = capabilities.maxImageCount;

    VkSwapchainCreateInfoKHR createInfo = {0};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = stormsinger_vulkanGetSurface();
    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = format.format;
    createInfo.imageColorSpace = format.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    createInfo.preTransform = capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = mode;
    createInfo.clipped = VK_TRUE;
    createInfo.oldSwapchain = VK_NULL_HANDLE;

    uint32_t indices[2] = {stormsinger_vulkanGetGraphicsIndex(),
                           stormsinger_vulkanGetPresentIndex()};
    if (indices[0] != indices[1])
    {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = indices;
    }
    else createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateSwapchainKHR(logicalDevice, &createInfo, nullptr,
                             &pSwapchain) != VK_SUCCESS)
    {
        fprintf(stderr, "Failed to create swapchain.\n");
        return false;
    }

    vkGetSwapchainImagesKHR(logicalDevice, pSwapchain, &imageCount,
                            nullptr);
    VkImage *images = malloc(sizeof(VkImage) * imageCount);
    pSwapchainImages = malloc(sizeof(VkImageView) * imageCount);
    vkGetSwapchainImagesKHR(logicalDevice, pSwapchain, &imageCount,
                            images);

    VkImageViewCreateInfo imageCreateInfo = {0};
    imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    imageCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    imageCreateInfo.format = format.format;
    imageCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageCreateInfo.subresourceRange.aspectMask =
        VK_IMAGE_ASPECT_COLOR_BIT;
    imageCreateInfo.subresourceRange.baseMipLevel = 0;
    imageCreateInfo.subresourceRange.levelCount = 1;
    imageCreateInfo.subresourceRange.baseArrayLayer = 0;
    imageCreateInfo.subresourceRange.layerCount = 1;

    for (size_t i = 0; i < imageCount; i++)
    {
        imageCreateInfo.image = images[i];
        if (vkCreateImageView(logicalDevice, &imageCreateInfo, nullptr,
                              &pSwapchainImages[i]) != VK_SUCCESS)
        {
            fprintf(stderr, "Failed to create image view %zu.", i);
            return false;
        }
    }

    return true;
}
