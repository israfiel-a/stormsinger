#include <Vulkan/Device.h>
#include <Vulkan/Surface.h>
#include <stdio.h>
#include <stdlib.h>

static VkPhysicalDevice pPhysicalDevice = nullptr;
static VkDevice pLogicalDevice = nullptr;
static VkQueue pGraphicsQueue = nullptr;
static VkQueue pPresentQueue = nullptr;

uint32_t scoreDevice(VkPhysicalDevice device)
{
    VkPhysicalDeviceProperties properties;
    VkPhysicalDeviceFeatures features;
    vkGetPhysicalDeviceProperties(device, &properties);
    vkGetPhysicalDeviceFeatures(device, &features);

    uint32_t score = 0;
    switch (properties.deviceType)
    {
        case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:   score += 4; break;
        case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU: score += 3; break;
        case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:    score += 2; break;
        default:                                     score += 1; break;
    }

    // TODO: Extra grading to be done here.

    return score;
}

bool stormsinger_vulkanCreateDevice(VkInstance instance)
{
    uint32_t physicalCount = 0;
    vkEnumeratePhysicalDevices(instance, &physicalCount, nullptr);
    VkPhysicalDevice *physicalDevices =
        malloc(sizeof(VkPhysicalDevice) * physicalCount);
    vkEnumeratePhysicalDevices(instance, &physicalCount, physicalDevices);

    VkPhysicalDevice currentChosen = nullptr;
    uint32_t bestScore = 0;
    for (size_t i = 0; i < physicalCount; i++)
    {
        uint32_t score = scoreDevice(physicalDevices[i]);
        if (score > bestScore)
        {
            currentChosen = physicalDevices[i];
            bestScore = score;
        }
    }

    if (currentChosen == nullptr)
    {
        fprintf(stderr, "Failed to find suitable Vulkan device.\n");
        return false;
    }
    pPhysicalDevice = currentChosen;
    free(physicalDevices);

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(pPhysicalDevice,
                                             &queueFamilyCount, nullptr);

    VkQueueFamilyProperties *queueFamilies =
        malloc(sizeof(VkQueueFamilyProperties) * queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(
        pPhysicalDevice, &queueFamilyCount, queueFamilies);

    uint32_t graphicsQueue = 0, presentQueue = 0;
    bool foundGraphicsQueue = false, foundPresentQueue = false;
    for (size_t i = 0; i < queueFamilyCount; i++)
    {
        if (foundGraphicsQueue && foundPresentQueue) break;

        VkQueueFamilyProperties family = queueFamilies[i];
        if (family.queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            graphicsQueue = i;
            foundGraphicsQueue = true;
        }

        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(
            pPhysicalDevice, i, stormsinger_vulkanGetSurface(),
            &presentSupport);
        if (presentSupport)
        {
            presentQueue = i;
            foundPresentQueue = true;
        }
    }

    if (!foundGraphicsQueue)
    {
        fprintf(stderr, "Failed to find graphics queue.\n");
        return false;
    }

    if (!foundPresentQueue)
    {
        fprintf(stderr, "Failed to find presentation queue.\n");
        return false;
    }

    float priority = 1.0f;
    VkDeviceQueueCreateInfo queueCreateInfos[2] = {{0}, {0}};
    queueCreateInfos[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfos[0].queueFamilyIndex = graphicsQueue;
    queueCreateInfos[0].queueCount = 1;
    queueCreateInfos[0].pQueuePriorities = &priority;

    queueCreateInfos[1].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfos[1].queueFamilyIndex = presentQueue;
    queueCreateInfos[1].queueCount = 1;
    queueCreateInfos[1].pQueuePriorities = &priority;

    // We don't need any features at the moment.
    VkPhysicalDeviceFeatures usedFeatures = {0};

    VkDeviceCreateInfo logicalDeviceCreateInfo = {0};
    logicalDeviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    logicalDeviceCreateInfo.pQueueCreateInfos = queueCreateInfos;
    if (presentQueue != graphicsQueue)
        logicalDeviceCreateInfo.queueCreateInfoCount = 2;
    else logicalDeviceCreateInfo.queueCreateInfoCount = 1;
    logicalDeviceCreateInfo.pEnabledFeatures = &usedFeatures;

    // Layers for logical devices no longer need to be set in newer
    // implementations.

    VkResult code =
        vkCreateDevice(pPhysicalDevice, &logicalDeviceCreateInfo, nullptr,
                       &pLogicalDevice);
    if (code != VK_SUCCESS)
    {
        fprintf(stderr, "Failed to create logical device. Code: %d.\n",
                code);
        return false;
    }

    vkGetDeviceQueue(pLogicalDevice, graphicsQueue, 0, &pGraphicsQueue);
    vkGetDeviceQueue(pLogicalDevice, presentQueue, 0, &pPresentQueue);

    return true;
}
